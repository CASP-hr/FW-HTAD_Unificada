#include "Driver_Analog.h"
#include <xc.h>
#include "ServiceTimer.h"

#define NUM_SAMPLES 10 // N�mero de amostras para m�dia
#define ADC_CHANNEL_AN0 0 // Canal do ADC para AN0
#define ADC_CHANNEL_AN1 1 // Canal do ADC para AN1
#define ADC_CHANNEL_AN3 3 // Canal do ADC para AN3

// Vari�veis para armazenar os valores lidos do ADC
static uint16_t adc_values_an0[NUM_SAMPLES];
static uint16_t adc_values_an1[NUM_SAMPLES];
static uint16_t adc_values_an3[NUM_SAMPLES];
static uint8_t sample_index = 0;
static uint32_t lastReadTime = 0;

// Fun��o que realiza o mapeamento de valores
uint16_t mapValue(uint16_t value, uint16_t inMin, uint16_t inMax, uint16_t outMin, uint16_t outMax) {
    return (uint16_t)(((uint32_t)value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin);
}

// Fun��o de inicializa��o do driver anal�gico
void Driver_Analog_Init() {
    // Configura��o do ADC
    ADCON0 = 0x01; // Habilita o ADC e configura o clock
    ADCON1 = 0x80; // Configura as entradas anal�gicas como refer�ncia VDD
    ADCON2 = 0x92; // Configura a justifica��o � direita e o tempo de convers�o
}

// Fun��o que realiza a leitura peri�dica das entradas anal�gicas
void Driver_Analog_Run() {
    uint32_t currentTick = SRV_TIMER_GetTick(); // Obter o tick atual em milissegundos

    // Verificar se o intervalo de 100 ms se passou
    if ((currentTick - lastReadTime) >= 100) {
        lastReadTime = currentTick; // Atualizar o tick da �ltima leitura

        // Leitura das entradas anal�gicas AN0, AN1 e AN3
        ADCON0bits.CHS = ADC_CHANNEL_AN0; // Seleciona o canal AN0
        ADCON0bits.GO_nDONE = 1; // Inicia a convers�o
        while (ADCON0bits.GO_nDONE); // Aguarda a convers�o ser conclu�da
        adc_values_an0[sample_index] = (ADRESH << 8) | ADRESL;

        ADCON0bits.CHS = ADC_CHANNEL_AN1; // Seleciona o canal AN1
        ADCON0bits.GO_nDONE = 1; // Inicia a convers�o
        while (ADCON0bits.GO_nDONE); // Aguarda a convers�o ser conclu�da
        adc_values_an1[sample_index] = (ADRESH << 8) | ADRESL;

        ADCON0bits.CHS = ADC_CHANNEL_AN3; // Seleciona o canal AN3
        ADCON0bits.GO_nDONE = 1; // Inicia a convers�o
        while (ADCON0bits.GO_nDONE); // Aguarda a convers�o ser conclu�da
        adc_values_an3[sample_index] = (ADRESH << 8) | ADRESL;

        // Incrementa o �ndice para a pr�xima amostra e faz a m�dia dos valores
        sample_index++;
        if (sample_index >= NUM_SAMPLES) {
            sample_index = 0;
        }
    }
}

// Fun��o que retorna o valor m�dio da entrada AN0
uint16_t Driver_Analog_GetValueAN0() {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
        sum += adc_values_an0[i];
    }
    uint16_t averageValue = (uint16_t)(sum / NUM_SAMPLES);
    return mapValue(averageValue, 0, 1023, 0, 4095);
}

// Fun��o que retorna o valor m�dio da entrada AN1
uint16_t Driver_Analog_GetValueAN1() {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
        sum += adc_values_an1[i];
    }
    uint16_t averageValue = (uint16_t)(sum / NUM_SAMPLES);
    return mapValue(averageValue, 0, 1023, 0, 4095);

}

// Fun��o que retorna o valor m�dio da entrada AN3
uint16_t Driver_Analog_GetValueAN3() {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
        sum += adc_values_an3[i];
    }
    uint16_t averageValue = (uint16_t)(sum / NUM_SAMPLES);
    return mapValue(averageValue, 0, 1023, 0, 4095);
}

