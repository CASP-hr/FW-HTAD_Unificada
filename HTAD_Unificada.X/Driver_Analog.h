#ifndef DRIVER_ANALOG_H
#define DRIVER_ANALOG_H

#include <stdint.h>

// Função de inicialização do driver analógico
void Driver_Analog_Init();

// Função que realiza a leitura periódica das entradas analógicas
void Driver_Analog_Run();

// Função que retorna o valor médio da entrada AN0
uint16_t Driver_Analog_GetValueAN0();

// Função que retorna o valor médio da entrada AN1
uint16_t Driver_Analog_GetValueAN1();

// Função que retorna o valor médio da entrada AN3
uint16_t Driver_Analog_GetValueAN3();

#endif // DRIVER_ANALOG_H

