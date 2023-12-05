/* 
 * File:   DRV_Sensor_ADT7410TRZ.h
 * Author: flavio.luciano
 *
 * Created on September 8, 2020, 11:39 AM
 */

#ifndef DRIVERADT7410TRZ_H
#define	DRIVERADT7410TRZ_H

#include <stdint.h>
#include <stdio.h>
#include "mcc_generated_files/i2c1_master.h"




#ifdef	__cplusplus
extern "C" {
#endif
  
    void DRV_ADT7410_Read(i2c1_address_t address, uint8_t reg, uint8_t *data, size_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_SENSOR_ADT7410TRZ_H */

