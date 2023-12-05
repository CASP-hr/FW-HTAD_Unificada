
#include "Driver_DirectNet.h"
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>  // Inclua a biblioteca apropriada para o seu compilador PIC
#include <string.h>
#include "ServiceTimer.h"
#include "ServiceADT7410.h"
#include "Driver_Analog.h"
#define _XTAL_FREQ 40000000

// Defina os valores dos caracteres de controle do protocolo DirectNet
#define ENQ 0x05
#define ACK 0x06
#define NAK 0x15
#define SOH 0x01
#define ETB 0x17
#define STX 0x02
#define ETX 0x03
#define EOT 0x04

bool recebeu_Serial = false;
unsigned long tempo = 0; // "Timer" para saber se a msg acabou
bool CPU_Comunicando = false;
uint8_t respondeHTAD = 0;
uint8_t ID_Responde = 0;

char recebeu[20];
uint16_t contRX = 0;  
uint8_t stateDirectNet = 0;
uint8_t recebeuID = 0;
    

uint8_t bufferEnvio[30];
uint8_t bufferLcr[30];
uint8_t bufferDadosCELSIUS[4];
uint8_t bufferDadosFAHRENHEIT[5];
uint8_t bufferDadosValorBruto[7];  
uint8_t bufferDadosDDDTCO2[30]; 


// Função para calcular o LRC de um buffer de dados
uint8_t calculateLRC(uint8_t* data, uint8_t dataLength) {
    uint8_t lrc = 0;
    for (uint8_t i = 0; i < dataLength; i++) {
        lrc ^= data[i];
    }
    return lrc;
}

void DirectNet_enviaDadosDDDTCO2(void)
{
   

    uint8_t LCR = calculateLRC(bufferDadosDDDTCO2,23);
    
    bufferEnvio[0] = ACK;// HTAD responde ACK
    bufferEnvio[1] = STX;// HTAD responde STX
    bufferEnvio[2] =  bufferDadosDDDTCO2[0];
    bufferEnvio[3] =  bufferDadosDDDTCO2[1];
    bufferEnvio[4] =  bufferDadosDDDTCO2[2];
    bufferEnvio[5] =  bufferDadosDDDTCO2[3];
    bufferEnvio[6] =  bufferDadosDDDTCO2[4];
    bufferEnvio[7] =  bufferDadosDDDTCO2[5];
    bufferEnvio[8] =  bufferDadosDDDTCO2[6];
    bufferEnvio[9] =  bufferDadosDDDTCO2[7];
    bufferEnvio[10] = bufferDadosDDDTCO2[8];
    bufferEnvio[11] = bufferDadosDDDTCO2[9];
    bufferEnvio[12] = bufferDadosDDDTCO2[10];
    bufferEnvio[13] = bufferDadosDDDTCO2[11];
    bufferEnvio[14] = bufferDadosDDDTCO2[12];
    bufferEnvio[15] = bufferDadosDDDTCO2[13];
    bufferEnvio[16] = bufferDadosDDDTCO2[14];
    bufferEnvio[17] = bufferDadosDDDTCO2[15];
    bufferEnvio[18] = bufferDadosDDDTCO2[16];
    bufferEnvio[19] = bufferDadosDDDTCO2[17];
    bufferEnvio[20] = bufferDadosDDDTCO2[18];
    bufferEnvio[21] = bufferDadosDDDTCO2[19];
    bufferEnvio[22] = bufferDadosDDDTCO2[20];
    bufferEnvio[23] = bufferDadosDDDTCO2[21];
    bufferEnvio[24] = bufferDadosDDDTCO2[22]; 
    
    bufferEnvio[25] = ETX; // HTAD responde ETX
    bufferEnvio[26] = LCR; // calculo LCR dos dados   
  //  bufferEnvio[27] = 0xAA; 
  //  bufferEnvio[27] = 0x00; 
    
    //ID 11  com 23 bytes

    int i;
    for (i = 0; i < 27; i++) {
      //  TX_Enable_SetHigh(); // habilita escrita 485
        EUSART1_Write(bufferEnvio[i]);                
    }
}

void DirectNet_enviaDadosSensores(void)
{
    bufferLcr[0] = 0xAA; //  perguntar bau pq 0xAA ?;
    bufferLcr[1] = 0x00; //  perguntar bau pq 0x00 ?
    bufferLcr[2] = 0x00; //  perguntar bau pq 0x00 ?
    bufferLcr[3] = 0x00; //  espaço
    bufferLcr[4] = bufferDadosValorBruto[0];// HTAD responde Valor bruto
    bufferLcr[5] = bufferDadosValorBruto[1];// HTAD responde Valor bruto
    bufferLcr[6] = 0x00; //  perguntar bau pq 0x00 ?
    bufferLcr[7] = bufferDadosCELSIUS[0];// HTAD responde Valor CELSIUS
    bufferLcr[8] = bufferDadosCELSIUS[1];// HTAD responde Valor CELSIUS
    bufferLcr[9] = bufferDadosCELSIUS[2];// HTAD responde Valor CELSIUS
    bufferLcr[10] = bufferDadosCELSIUS[3];// HTAD responde Valor CELSIUS
    bufferLcr[11] = bufferDadosFAHRENHEIT[0];// HTAD responde Valor FAHRENHEIT
    bufferLcr[12] = bufferDadosFAHRENHEIT[1];// HTAD responde Valor FAHRENHEIT
    bufferLcr[13] = bufferDadosFAHRENHEIT[2];// HTAD responde Valor FAHRENHEIT
    bufferLcr[14] = bufferDadosFAHRENHEIT[3];// HTAD responde Valor FAHRENHEIT
    bufferLcr[15] = bufferDadosFAHRENHEIT[4];// HTAD responde Valor FAHRENHEIT
    bufferLcr[16] = 0x00;
    bufferLcr[17] = 0x00;
    bufferLcr[18] = ID_Responde; // HTAD responde ID
    bufferLcr[19] = 0x00; //  perguntar bau pq 0x00 ?
    bufferLcr[20] = 0x55; //  perguntar bau pq 0x55 ?

    uint8_t LCR = calculateLRC(bufferLcr,21);


    bufferEnvio[0] = ACK;// HTAD responde ACK
    bufferEnvio[1] = STX;// HTAD responde STX
    bufferEnvio[2] = 0xAA; //  perguntar bau pq 0xAA ?
    bufferEnvio[3] = 0x00; //  perguntar bau pq 0x00 ?
    bufferEnvio[4] = 0x00; //  perguntar bau pq 0x00 ?
    bufferEnvio[5] = 0x00; //  espaço
    bufferEnvio[6] = bufferDadosValorBruto[0];// HTAD responde Valor bruto
    bufferEnvio[7] = bufferDadosValorBruto[1];// HTAD responde Valor bruto
    bufferEnvio[8] = 0x00; //  perguntar bau pq 0x00 ?
    bufferEnvio[9] = bufferDadosCELSIUS[0];// HTAD responde Valor CELSIUS
    bufferEnvio[10] = bufferDadosCELSIUS[1];// HTAD responde Valor CELSIUS
    bufferEnvio[11] = bufferDadosCELSIUS[2];// HTAD responde Valor CELSIUS
    bufferEnvio[12] = bufferDadosCELSIUS[3];// HTAD responde Valor CELSIUS
    bufferEnvio[13] = bufferDadosFAHRENHEIT[0];// HTAD responde Valor FAHRENHEIT
    bufferEnvio[14] = bufferDadosFAHRENHEIT[1];// HTAD responde Valor FAHRENHEIT
    bufferEnvio[15] = bufferDadosFAHRENHEIT[2];// HTAD responde Valor FAHRENHEIT
    bufferEnvio[16] = bufferDadosFAHRENHEIT[3];// HTAD responde Valor FAHRENHEIT
    bufferEnvio[17] = bufferDadosFAHRENHEIT[4];// HTAD responde Valor FAHRENHEIT
    bufferEnvio[18] = 0x00;
    bufferEnvio[19] = 0x00;
    bufferEnvio[20] = ID_Responde; // HTAD responde ID
    bufferEnvio[21] = 0x00; //  perguntar bau pq 0x00 ?
    bufferEnvio[22] = 0x55; //  perguntar bau pq 0x55 ?
    bufferEnvio[23] = ETX; // HTAD responde ETX
    bufferEnvio[24] = LCR; // calculo LCR dos dados   
  //  bufferEnvio[25] = 0xAA; 
  //  bufferEnvio[25] = 0x00; 
   // 21 bytes ID 2 , 3 , 4
    int i;
    for (i = 0; i < 25; i++) {
        //TX_Enable_SetHigh(); // habilita escrita 485
        EUSART1_Write(bufferEnvio[i]);                
    }
}

void convertFloatToBuffer(float value, uint8_t* buffer, uint8_t bufferSize) {
    int val = value * 100;
    for (size_t i = 0; i < bufferSize; i++) {
        buffer[i] = val % 10;
        val /= 10;
    }
}

void DirectNet_Send(void){
    
    if (EUSART1_is_rx_ready()) {
        // Ler o dado recebido da UART e armazená-lo no buffer
        uint8_t rx  = EUSART1_Read();      
        recebeu[contRX] = rx; 
        contRX++; 
        tempo = SRV_TIMER_GetTick();
        recebeu_Serial = true;       
    } 
}

void DirectNet_Run(Object_t* objetoHTAD_DirectNet) {
   
    int i = 0;
       
    // Se recebeu algum dado e está a 4ms sem receber mais, processar a mensagem
    if ((SRV_TIMER_GetTick()  - tempo > 10) && recebeu_Serial){
        TX_Enable_SetHigh(); // habilita escrita 485
        
        objetoHTAD_DirectNet->contWDT++;
        
        for (i = 0; i < contRX; i++) {  
            if(recebeu[i] == 0x4E && recebeu[i + 2] == 0x05){
              stateDirectNet = 0;  
            }
        }
        
        switch(stateDirectNet) 
        {
            case 0:
                i = 0;
                for (i = 0; i < contRX; i++) {                
                   if(recebeu[i] == 0x4E && recebeu[i + 2] == 0x05){
                        EUSART1_Write(0x4E); // HTAD responde 4e 22 06
                        EUSART1_Write(recebeu[i+1]);
                        EUSART1_Write(0x06); 
                        stateDirectNet = 1;
                        recebeuID = recebeu[i+1];  
                        respondeHTAD = recebeuID;
                        if(recebeuID == 0x2B){
                          respondeHTAD = 0x32;  
                        } 
                        objetoHTAD_DirectNet->contWDT = 0;
                        break;
                    }
                }               
                break;
            case 1:
                i = 0;     
                for (i = 0; i < contRX; i++) { 

                    if( recebeu[i] == 0x01 && recebeu[i + 1] == 0x30 && recebeu[i + 2] == respondeHTAD + 0x10 /*&&
                        recebeu[i + 3] == 0x30 && recebeu[i + 4] == 0x30 && recebeu[i + 5] == 0x30 &&
                        recebeu[i + 6] == 0x30 && recebeu[i + 7] == 0x30 && recebeu[i + 8] == 0x30 &&
                        recebeu[i + 9] == 0x30 && recebeu[i + 10] == 0x30 && recebeu[i + 11] == 0x31 &&
                        recebeu[i + 12] == 0x35 && recebeu[i + 13] == 0x30 && recebeu[i + 14] == 0x31*/  &&
                        recebeu[i + 15] == 0x17)
                    { 
                        objetoHTAD_DirectNet->contWDT = 0;    
                        if(recebeuID == 0x22){  

                            objetoHTAD_DirectNet->temperatureS1 = SRV_ADT7410_GetTemperature(SENSOR_S1, CELSIUS);                                 
                            int valBruto = objetoHTAD_DirectNet->temperatureS1 * 128;
                            bufferDadosValorBruto[1] = valBruto >> 8;
                            bufferDadosValorBruto[0] = valBruto;                                
                            convertFloatToBuffer(objetoHTAD_DirectNet->temperatureS1,bufferDadosCELSIUS,sizeof(bufferDadosCELSIUS)); 
                            objetoHTAD_DirectNet->temperatureS1 = SRV_ADT7410_GetTemperature(SENSOR_S1, FAHRENHEIT);                                
                            convertFloatToBuffer(objetoHTAD_DirectNet->temperatureS1,bufferDadosFAHRENHEIT,sizeof(bufferDadosFAHRENHEIT)); 
                            ID_Responde = 0x22;
                            DirectNet_enviaDadosSensores();

                        } 
                        else if(recebeuID == 0x24){  
                            objetoHTAD_DirectNet->temperatureS2 = SRV_ADT7410_GetTemperature(SENSOR_S2, CELSIUS);                                 
                            int valBruto = objetoHTAD_DirectNet->temperatureS2 * 128;
                            bufferDadosValorBruto[1] = valBruto >> 8;
                            bufferDadosValorBruto[0] = valBruto;                                
                            convertFloatToBuffer(objetoHTAD_DirectNet->temperatureS2,bufferDadosCELSIUS,sizeof(bufferDadosCELSIUS)); 
                            objetoHTAD_DirectNet->temperatureS2 = SRV_ADT7410_GetTemperature(SENSOR_S2, FAHRENHEIT);                                
                            convertFloatToBuffer(objetoHTAD_DirectNet->temperatureS2,bufferDadosFAHRENHEIT,sizeof(bufferDadosFAHRENHEIT)); 
                            ID_Responde = 0x24;
                            DirectNet_enviaDadosSensores();

                        } 
                        else if(recebeuID == 0x23){  
                            objetoHTAD_DirectNet->temperatureS3 = SRV_ADT7410_GetTemperature(SENSOR_S3, CELSIUS);                                 
                            int valBruto = objetoHTAD_DirectNet->temperatureS3 * 128;
                            bufferDadosValorBruto[1] = valBruto >> 8;
                            bufferDadosValorBruto[0] = valBruto;                                
                            convertFloatToBuffer(objetoHTAD_DirectNet->temperatureS3,bufferDadosCELSIUS,sizeof(bufferDadosCELSIUS)); 
                            objetoHTAD_DirectNet->temperatureS3 = SRV_ADT7410_GetTemperature(SENSOR_S3, FAHRENHEIT);                                
                            convertFloatToBuffer(objetoHTAD_DirectNet->temperatureS3,bufferDadosFAHRENHEIT,sizeof(bufferDadosFAHRENHEIT)); 
                            ID_Responde = 0x23;
                            DirectNet_enviaDadosSensores();

                        }
                        else if(recebeuID == 0x2B){  


                            objetoHTAD_DirectNet->DD = Driver_Analog_GetValueAN0();
                            objetoHTAD_DirectNet->DT = Driver_Analog_GetValueAN1();
                            objetoHTAD_DirectNet->CO2 = Driver_Analog_GetValueAN3(); 

                            int valBruto = objetoHTAD_DirectNet->DD;

                            bufferDadosDDDTCO2[0] = 0xAA;
                            bufferDadosDDDTCO2[1] = 0x00;
                            bufferDadosDDDTCO2[2] = 0x00;
                            bufferDadosDDDTCO2[3] = 0x00;
                            bufferDadosDDDTCO2[4] = 0x00;
                            bufferDadosDDDTCO2[5] = 0x00;
                            bufferDadosDDDTCO2[6] = 0x00;
                            bufferDadosDDDTCO2[7] = 0x00;
                            bufferDadosDDDTCO2[8] = 0x00;

                                
                            valBruto = objetoHTAD_DirectNet->DD;
                                                       
                                    
                            bufferDadosDDDTCO2[10] = valBruto >> 8;
                            bufferDadosDDDTCO2[9] = valBruto;

                            valBruto = valBruto = objetoHTAD_DirectNet->DT;

                            bufferDadosDDDTCO2[12] = valBruto >> 8;
                            bufferDadosDDDTCO2[11] = valBruto;

                            valBruto = objetoHTAD_DirectNet->CO2;

                            bufferDadosDDDTCO2[14] = valBruto >> 8;
                            bufferDadosDDDTCO2[13] = valBruto; 

                            bufferDadosDDDTCO2[15] = 0xFF; 
                            bufferDadosDDDTCO2[16] = 0xFF; 
                            bufferDadosDDDTCO2[17] = 0xFF; 
                            bufferDadosDDDTCO2[18] = 0xFF; 
                            bufferDadosDDDTCO2[19] = 0xFF; 
                            bufferDadosDDDTCO2[20] = 0xFF; 
                            bufferDadosDDDTCO2[21] = 0xFF; 
                            bufferDadosDDDTCO2[22] = 0xFF;
                            DirectNet_enviaDadosDDDTCO2();
                        }                           
                       stateDirectNet = 2;                             
                       break;
                    }
                    else{
                      EUSART1_Write(0x04); 
                      stateDirectNet = 0;   
                    }                    
                }           
                //stateDirectNet = 2;                                       
                break;   
            case 2:
                i = 0;     
                for (i = 0; i < contRX; i++) { 
                    if( recebeu[i] == 0x06){
                        EUSART1_Write(0x04); 
                        objetoHTAD_DirectNet->contWDT = 0;
                       break; 
                    }
                } 
                stateDirectNet = 0;
                break;
        }  
         
        i = 0;
        while(EUSART1_is_tx_done() == false){i++;recebeu[i] = 0;if(i > contRX)i = 0; }    
        TX_Enable_SetLow();
       // Reiniciar as variáveis para receber a próxima mensagem
       contRX = 0;
       recebeu_Serial = false;        
    }

    
    
}


void DirectNet_Init(void) {
   
}

