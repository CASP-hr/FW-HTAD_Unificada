#include "Driver_EEPROM.h"
#include <xc.h>

// Register: EEADRH
#define EEADRH EEADRH
extern volatile unsigned char EEADRH __at(0xFAA);

void EEPROM_Init() {
    // Configurações iniciais para a EEPROM (não é necessária para o PIC18F25K22)
    // Pode ser deixado vazio, caso não haja configurações específicas.
}

void EEPROM_WriteBytes(uint16_t address, uint8_t* data, uint8_t numBytes) {
    uint16_t timeOut = 0;
    
    // Verifica se o número de bytes é válido (máximo 6 bytes, de acordo com o seu requisito)
    if (numBytes > 6) {
        return; // Ou pode lançar um erro ou realizar alguma ação de tratamento adequada
    }

    // Escreve os dados na EEPROM
    for (uint8_t i = 0; i < numBytes; i++) {
        // Aguarda a conclusão de qualquer operação anterior
          while (EECON1bits.WR || EECON1bits.RD || EECON1bits.CFGS){
              timeOut++;
              if(timeOut > 10000){
                  break;
              }
          }

        // Carrega o endereço do byte a ser gravado
        EEADR = (uint8_t)address; // 8 bits menos significativos
        EEADRH = (uint8_t)(address >> 8); // 8 bits mais significativos

        EEDATA = data[i];

        // Habilita a escrita na EEPROM e inicia a operação de escrita
        EECON1bits.WREN = 1;
        INTCONbits.GIE = 0; // Desabilita interrupções para evitar problemas com escrita
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        INTCONbits.GIE = 1; // Reabilita interrupções

        // Aguarda a conclusão da escrita
        while (EECON1bits.WR)
            continue;

        EECON1bits.WREN = 0; // Desabilita a escrita na EEPROM

        // Incrementa o endereço para o próximo byte
        address++;
    }
}

uint8_t EEPROM_ReadByte(uint16_t address) {
    uint16_t timeOut = 0;
    // Aguarda a conclusão de qualquer operação anterior
     while (EECON1bits.WR || EECON1bits.RD || EECON1bits.CFGS){
         timeOut++;
              if(timeOut > 10000){
                  break;
              }
     }

    // Carrega o endereço do byte a ser lido
    EEADR = (uint8_t)address; // 8 bits menos significativos
    EEADRH = (uint8_t)(address >> 8); // 8 bits mais significativos

    // Executa a leitura
    EECON1bits.RD = 1;

    // Retorna o dado lido
    return EEDATA;
}

