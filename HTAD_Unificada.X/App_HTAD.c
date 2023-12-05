#include "App_HTAD.h"
#include "Driver_LCD.h"
#include "SRV_Display.h"
#include "ServiceADT7410.h"
#include "ServiceTimer.h"
#include "Driver_Analog.h"
#include "Utilities.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr0.h"
#include "Driver_EEPROM.h"
#include "Driver_DirectNet.h"
#include "mcc_generated_files/memory.h"

#define _XTAL_FREQ 40000000

Estado_e stateHTAD;        
ptrFunction mchStateHTAD[15]; 
Object_t ObjetoHTAD;



// <editor-fold defaultstate="collapsed" desc="Gravação e leitura da EEPROM">
// Função para gravar os valores na EEPROM
void gravarDadosNaEEPROM() {
    // Define o endereço de início na EEPROM onde os dados serão armazenados
    uint8_t enderecoEEPROM = 0x01; // Você pode ajustar o endereço conforme necessário

    // Escreve os valores dos atributos na EEPROM
    DATAEE_WriteByte(enderecoEEPROM++, ObjetoHTAD.erroSensorS1.positivo );
    DATAEE_WriteByte(enderecoEEPROM++, ObjetoHTAD.erroSensorS1.negativo);
    DATAEE_WriteByte(enderecoEEPROM++, ObjetoHTAD.erroSensorS2.positivo);
    DATAEE_WriteByte(enderecoEEPROM++, ObjetoHTAD.erroSensorS2.negativo);
    DATAEE_WriteByte(enderecoEEPROM++, ObjetoHTAD.erroSensorS3.positivo);
    DATAEE_WriteByte(enderecoEEPROM++, ObjetoHTAD.erroSensorS3.negativo);
}

// Função para ler os valores da EEPROM
void lerDadosDaEEPROM() {
        
    // Define o endereço de início na EEPROM onde os dados foram armazenados
    uint8_t enderecoEEPROM = 0x01; // Mesmo endereço usado para gravar os dados
    
    if(DATAEE_ReadByte(0x00) == 0xFF){
         int i;
        for (i = 0; i < 10; i++) {
            DATAEE_WriteByte(0x00+i,0);
        }
    }    
    // Lê os valores dos atributos da EEPROM
    ObjetoHTAD.erroSensorS1.positivo  = DATAEE_ReadByte(enderecoEEPROM++);
    ObjetoHTAD.erroSensorS1.negativo = DATAEE_ReadByte(enderecoEEPROM++);
    ObjetoHTAD.erroSensorS2.positivo = DATAEE_ReadByte(enderecoEEPROM++);
    ObjetoHTAD.erroSensorS2.negativo = DATAEE_ReadByte(enderecoEEPROM++);
    ObjetoHTAD.erroSensorS3.positivo = DATAEE_ReadByte(enderecoEEPROM++);
    ObjetoHTAD.erroSensorS3.negativo = DATAEE_ReadByte(enderecoEEPROM++);      
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Main e init APP">

void App_HTAD_ClearWDT()
{   
    CLRWDT();
}


void App_HTAD_init()
{  
   
    SRV_Display_Init();
    SRV_ADT7410_Init();
    TMR0_Initialize();
    SRV_TIMER_Init(); 
    DRV_LCD_Clear();   
    Driver_Analog_Init(); 
    DirectNet_Init();   
    stateHTAD = HOME;
    mchStateHTAD[HOME] = App_HTAD_Home;
    mchStateHTAD[MenuAjusteErro] = App_HTAD_MenuAjusteErro;
        
    lerDadosDaEEPROM();
             
    PIE1bits.RC1IE = 1; // Habilita a interrupção de recepção da UART
    INTCONbits.PEIE = 1; // Habilita as interrupções de periféricos (Peripheral Interrupt)
    INTCONbits.GIE = 1; // Habilita as interrupções globais
    
    SRV_ADT7410_SetErrorSensor(1,ObjetoHTAD.erroSensorS1.positivo,ObjetoHTAD.erroSensorS1.negativo);
    SRV_ADT7410_SetErrorSensor(2,ObjetoHTAD.erroSensorS2.positivo,ObjetoHTAD.erroSensorS2.negativo);
    SRV_ADT7410_SetErrorSensor(3,ObjetoHTAD.erroSensorS2.positivo,ObjetoHTAD.erroSensorS3.negativo);
            
    ObjetoHTAD.ResetWDT = false;

}

void App_HTAD_run()
{
    SRV_ADT7410_Run();  
    Driver_Analog_Run();
    DirectNet_Run(&ObjetoHTAD); 
    mchStateHTAD[stateHTAD](&ObjetoHTAD); 
    if(ObjetoHTAD.ResetWDT == false){
        CLRWDT();
    }
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Menu HOME">

void App_HTAD_UpdateDIrectNet(void){
   DirectNet_Run(&ObjetoHTAD);     
}
void App_HTAD_Home(Object_t* objetoHTAD)
{
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    char txt[21];
    static bool isCelsius = true;
    
    if(objetoHTAD->contWDT >= 10){
        objetoHTAD->ResetWDT = true;
    }   
       
    tick = SRV_TIMER_GetTick();
    
    if ((uint32_t)(tick - tickLast) >= 200)        
    {
        tickLast = tick;
        
        Led_State_Toggle();        
        
        TypeRead_e typeRead = isCelsius ? CELSIUS : FAHRENHEIT; // Define o tipo de leitura (Celsius ou Fahrenheit)
                
        objetoHTAD->temperatureS1 = SRV_ADT7410_GetTemperature(SENSOR_S1, typeRead);
        objetoHTAD->temperatureS2 = SRV_ADT7410_GetTemperature(SENSOR_S2, typeRead);
        objetoHTAD->temperatureS3 = SRV_ADT7410_GetTemperature(SENSOR_S3, typeRead);
        
        objetoHTAD->DD = Driver_Analog_GetValueAN0();
        objetoHTAD->DT = Driver_Analog_GetValueAN1();
        objetoHTAD->CO2 = Driver_Analog_GetValueAN3();                        

        // Exibe as temperaturas no formato desejado (Celsius ou Fahrenheit)
        sprintf(txt, "S1:% 3.2f\xDF""%c DD:%4d ", objetoHTAD->temperatureS1, isCelsius ? 'C' : 'F',objetoHTAD->DD);
        SRV_Display_Write(1, 1, txt);

        sprintf(txt, "S2:% 3.2f\xDF""%c DT:%4d ", objetoHTAD->temperatureS2, isCelsius ? 'C' : 'F',objetoHTAD->DT);
        SRV_Display_Write(2, 1, txt);

        sprintf(txt, "S3:% 3.2f\xDF""%c CO2:%4d", objetoHTAD->temperatureS3, isCelsius ? 'C' : 'F',objetoHTAD->CO2);
        SRV_Display_Write(3, 1, txt);
        // Exibe a senha
        sprintf(txt, "Menu C/F     Senha:%1d", objetoHTAD->senha);
        SRV_Display_Write(4, 1, txt);
    
    }
    
    // Leitura das teclas
    Key_e key = readKeypad();
    
    if(key == T1){
        if(objetoHTAD->senha == 3){
            objetoHTAD->senha = 0;
            stateHTAD = MenuAjusteErro;
        }
    }
    if (key == T2) {
        isCelsius = !isCelsius; // Inverte o modo de exibição entre Celsius e Fahrenheit
    }         
    if (key == T5) {;;
        objetoHTAD->senha ++;
        if(objetoHTAD->senha > 9){
            objetoHTAD->senha = 0;
        }
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Menu ajustes sensores">
void incrementDigit(uint8_t *valorSensor, uint8_t CursorLinha, uint8_t CursorColuna) {
    int digito1, digito2;

    digito1 = (*valorSensor / 10) % 10; // Obtém o dígito 1
    digito2 = *valorSensor % 10; // Obtém o dígito 2

    if (CursorColuna == 10 || CursorColuna == 18) {
        digito1 = (digito1 + 1) % 10; // Incrementa o dígito 1 e faz o ciclo de 0 a 9
    } else if (CursorColuna == 11 || CursorColuna == 19) {
        digito2 = (digito2 + 1) % 10; // Incrementa o dígito 2 e faz o ciclo de 0 a 9
    }

    *valorSensor = digito1 * 10 + digito2; // Atualiza o valor do sensor com os dígitos alterados
}

void decrementDigit(uint8_t *valorSensor, uint8_t CursorLinha, uint8_t CursorColuna) {
   
    int digito1, digito2;  

    digito1 = (*valorSensor / 10) % 10; // Obtém o dígito 1;
    digito2 = *valorSensor % 10; // Obtém o dígito 2

    if (CursorColuna == 10 || CursorColuna == 18) {
        digito1 = (digito1 + 9) % 10; // Decrementa o dígito 1 e faz o ciclo de 0 a 9
    } else if (CursorColuna == 11 || CursorColuna == 19) {
        digito2 = (digito2 + 9) % 10; // Decrementa o dígito 2 e faz o ciclo de 0 a 9
    }

    *valorSensor = digito1 * 10 + digito2; // Atualiza o valor do sensor com os dígitos alterados
}

void moveCursor(uint8_t *CursorLinha, uint8_t *CursorColuna) {
    if (*CursorColuna == 10) {
        *CursorColuna = 11;
    } else if (*CursorColuna == 11) {
        *CursorColuna = 18;
    } else if (*CursorColuna == 18) {
        *CursorColuna = 19;
    } else if (*CursorColuna == 19) {
        // Aproveitamos a aritmética modular para lidar com o CursorLinha cíclico
        *CursorLinha = (*CursorLinha % 3) + 1; // Incrementa de 1 a 3 ciclicamente
        *CursorColuna = 10;
    } 
}

void App_HTAD_MenuAjusteErro(Object_t* objetoHTAD) {
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    static uint8_t CursorLinha = 1;
    static uint8_t CursorColuna = 10;    
    
    static uint8_t stateteste = 0;
    char txt[20];        
    tick = SRV_TIMER_GetTick();    
    if ((uint32_t)(tick - tickLast) >= 250) {
        tickLast = tick;          
        
        // Exibe as temperaturas no formato desejado (Celsius ou Fahrenheit)
        sprintf(txt, "S1: Aj+: %02d Aj-: %02d ",objetoHTAD->erroSensorS1.positivo,objetoHTAD->erroSensorS1.negativo);        
        SRV_Display_Write(1, 1, txt); 
        sprintf(txt, "S2: Aj+: %02d Aj-: %02d ",objetoHTAD->erroSensorS2.positivo,objetoHTAD->erroSensorS2.negativo);       
        SRV_Display_Write(2, 1, txt); 
        sprintf(txt, "S3: Aj+: %02d Aj-: %02d ",objetoHTAD->erroSensorS3.positivo,objetoHTAD->erroSensorS3.negativo);        
        SRV_Display_Write(3, 1, txt);   
        sprintf(txt, "Sai INC DEC PRX SAV ");
        SRV_Display_Write(4, 1, txt); 
        DRV_LCD_SetCursor(CursorLinha, CursorColuna, 1); // abilita animação do cursor        
    }
    
    // Leitura das teclas
    Key_e key = readKeypad();  
   
    switch (key) {
        case T1: // Sai (sair do ajuste)
            lerDadosDaEEPROM();
            stateHTAD = HOME;           
            break;
        case T2: // Incrementa valor     
            switch (CursorLinha) {
            case 1:
                if (CursorColuna == 10 || CursorColuna == 11) {
                     incrementDigit(&objetoHTAD->erroSensorS1.positivo,CursorLinha,CursorColuna);
                }             
                else if (CursorColuna == 18 || CursorColuna == 19) {
                    incrementDigit(&objetoHTAD->erroSensorS1.negativo,CursorLinha,CursorColuna);
                }             
                break;
            case 2:
                if (CursorColuna == 10 || CursorColuna == 11) {
                     incrementDigit(&objetoHTAD->erroSensorS2.positivo,CursorLinha,CursorColuna);
                }             
                else if (CursorColuna == 18 || CursorColuna == 19) {
                    incrementDigit(&objetoHTAD->erroSensorS2.negativo,CursorLinha,CursorColuna);
                } 
                break;
            case 3:
               if (CursorColuna == 10 || CursorColuna == 11) {
                     incrementDigit(&objetoHTAD->erroSensorS3.positivo,CursorLinha,CursorColuna);
                }             
                else if (CursorColuna == 18 || CursorColuna == 19) {
                    incrementDigit(&objetoHTAD->erroSensorS3.negativo,CursorLinha,CursorColuna);
                } 
                break;      
            }                        
            break;
        case T3: // Decrementa valor  
            
            switch (CursorLinha) {
            case 1:
                if (CursorColuna == 10 || CursorColuna == 11) {
                     decrementDigit(&objetoHTAD->erroSensorS1.positivo,CursorLinha,CursorColuna);
                }             
                else if (CursorColuna == 18 || CursorColuna == 19) {
                    decrementDigit(&objetoHTAD->erroSensorS1.negativo,CursorLinha,CursorColuna);
                }             
                break;
            case 2:
                if (CursorColuna == 10 || CursorColuna == 11) {
                     decrementDigit(&objetoHTAD->erroSensorS2.positivo,CursorLinha,CursorColuna);
                }             
                else if (CursorColuna == 18 || CursorColuna == 19) {
                    decrementDigit(&objetoHTAD->erroSensorS2.negativo,CursorLinha,CursorColuna);
                } 
                break;
            case 3:
               if (CursorColuna == 10 || CursorColuna == 11) {
                     decrementDigit(&objetoHTAD->erroSensorS3.positivo,CursorLinha,CursorColuna);
                }             
                else if (CursorColuna == 18 || CursorColuna == 19) {
                    decrementDigit(&objetoHTAD->erroSensorS3.negativo,CursorLinha,CursorColuna);
                } 
                break;      
            }                         
            break;
        case T4: // Próximo dígito ou próximo erro
            moveCursor(&CursorLinha, &CursorColuna);   
            break;
        case T5: // Salvar
                // Escrita na EEPROM
            
                 gravarDadosNaEEPROM();
                 
                 lerDadosDaEEPROM();
           
            break;
        default:
            break;
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Leitura das Teclas">
Key_e readKeypad() {
    uint8_t currentKeyState = (TE0_GetValue() << 2) | (TE1_GetValue() << 1) | TE2_GetValue();

    // Variável para armazenar o estado anterior das teclas
    static uint8_t previousKeyState = 0xFF;
    // Variável para armazenar o tick atual
    static uint32_t lastKeyPressTime = 0;
    // Verifica se houve mudança no estado das teclas
    if (currentKeyState != previousKeyState) {
        // Armazena o tick atual
        uint32_t currentTick = SRV_TIMER_GetTick();
        // Verifica se houve uma mudança de tecla dentro do intervalo de debounce (30 ms)
        if ((currentTick - lastKeyPressTime) >= 30) {
            previousKeyState = currentKeyState;
            lastKeyPressTime = currentTick;

            // Verifica qual tecla foi pressionada
            if (currentKeyState == 0b011) return T1; // Tecla T1
            if (currentKeyState == 0b101) return T2; // Tecla T2
            if (currentKeyState == 0b001) return T3; // Tecla T3
            if (currentKeyState == 0b110) return T4; // Tecla T4 
            if (currentKeyState == 0b010) return T5; // Tecla T5 
            if (currentKeyState == 0b100) return T6; // Tecla T6 
            if (currentKeyState == 0b000) return T7; // Tecla T7
        }
    }
    // Se nenhuma tecla foi pressionada, retorne um valor inválido
    return NenhumaTecla; // Isso pode ser tratado como um valor inválido ou um "sem tecla pressionada"
}

// </editor-fold>