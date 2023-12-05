/* 
 * File:   Driver_DirectNet.h
 * Author: flavio.luciano
 *
 * Created on July 24, 2023, 3:34 PM
 */

#ifndef DRIVER_DIRECTNET_H
#define DRIVER_DIRECTNET_H

#include <stdbool.h>
#include <stdint.h>
#include "Utilities.h"

// Inicializa a comunicação DirectNet
void DirectNet_Init(void);

void DirectNet_Run(Object_t* objetoHTAD_DirectNet);

void DirectNet_Send(void);

#endif // DRIVER_DIRECTNET_H

