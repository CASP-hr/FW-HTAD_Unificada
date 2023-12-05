/* 
 * File:   Driver_EEPROM.h
 * Author: flavio.luciano
 *
 * Created on July 24, 2023, 9:42 AM
 */

#ifndef DRIVER_EEPROM_H
#define	DRIVER_EEPROM_H

#include <stdint.h>

void EEPROM_Init();

void EEPROM_WriteBytes(uint16_t address, uint8_t* data, uint8_t numBytes);
uint8_t EEPROM_ReadByte(uint16_t address);




#endif	/* DRIVER_EEPROM_H */

