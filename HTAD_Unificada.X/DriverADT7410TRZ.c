#include "DriverADT7410TRZ.h"
#include "mcc_generated_files/pin_manager.h"




typedef struct
{
    size_t len;
    uint8_t *data;
}i2c1_buffer_t;

static i2c1_operations_t rdBlkRegCompleteHandler(void *ptr);

static i2c1_operations_t rdBlkRegCompleteHandler(void *ptr)
{
    I2C1_SetBuffer(((i2c1_buffer_t *)ptr)->data,((i2c1_buffer_t*)ptr)->len);
    I2C1_SetDataCompleteCallback(NULL,NULL);
    return I2C1_RESTART_READ;
}


void DRV_ADT7410_Read(i2c1_address_t address, uint8_t reg, uint8_t *data, size_t len)
{  
    uint32_t timeOut = 0;
    i2c1_buffer_t bufferBlock; // result is little endian
    bufferBlock.data = data;
    bufferBlock.len = len;

    while(!I2C1_Open(address)){ // sit here until we get the bus..
       if(timeOut++ > 30)
        {
           timeOut = 0;
           return;
        }
    }
    I2C1_SetDataCompleteCallback(rdBlkRegCompleteHandler,&bufferBlock);
    I2C1_SetBuffer(&reg,1);
    I2C1_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C1_MasterWrite();
    while(I2C1_BUSY == I2C1_Close()){ // sit here until finished.
      if(timeOut++ > 30)
        {
           timeOut = 0;
           return;
        }
    }       
}