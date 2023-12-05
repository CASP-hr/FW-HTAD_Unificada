#ifndef DRIVER_ANALOG_H
#define DRIVER_ANALOG_H

#include <stdint.h>

// Fun��o de inicializa��o do driver anal�gico
void Driver_Analog_Init();

// Fun��o que realiza a leitura peri�dica das entradas anal�gicas
void Driver_Analog_Run();

// Fun��o que retorna o valor m�dio da entrada AN0
uint16_t Driver_Analog_GetValueAN0();

// Fun��o que retorna o valor m�dio da entrada AN1
uint16_t Driver_Analog_GetValueAN1();

// Fun��o que retorna o valor m�dio da entrada AN3
uint16_t Driver_Analog_GetValueAN3();

#endif // DRIVER_ANALOG_H

