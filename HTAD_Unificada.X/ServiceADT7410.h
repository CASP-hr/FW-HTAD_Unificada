/* 
 * File:   SRV_Sensor_ADT7410TRZ.h
 * Author: flavio.luciano
 *
 * Created on 9 de Setembro de 2020, 08:47
 */

#ifndef SERVICEADT7410_H
#define	SERVICEADT7410_H

#include <stdint.h>
#include <stdio.h>
#include "Utilities.h"

   void SRV_ADT7410_Init(void); 
   void SRV_ADT7410_Run(void);
   void SRV_ADT7410_On(void);
   void SRV_ADT7410_Off(void);   
   static uint16_t SRV_ADT7410_Read(Sensor_e address);
   
   void SRV_ADT7410_ReadMeanSensor(Sensor_e address,TypeRead_e typeRead , float *value);
   
   void SRV_ADT7410_SetErrorSensor(Sensor_e sensor, uint8_t error_pos, uint8_t error_neg);
   
   void SRV_ADT7410_multiplex_on(Sensor_e address);
   void SRV_ADT7410_multiplex_off(void);
   
   float SRV_ADT7410_GetTemperature(Sensor_e sensor ,TypeRead_e typeRead );

#endif	/* SRV_SENSOR_ADT7410TRZ_H */

