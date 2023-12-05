#include "ServiceADT7410.h"
#include "DriverADT7410TRZ.h"
#include "ServiceTimer.h"
#include "mcc_generated_files/mcc.h"
#include <string.h>
#include <stdio.h>
#include "Utilities.h"

typedef struct{
    float CELSIUS;
    float FAHRENHEIT;   
}Sensor_t;

Sensor_t Sensor1;
Sensor_t Sensor2;
Sensor_t Sensor3;

uint8_t errorPosSensorDianteiro;
uint8_t errorNegSensorDianteiro;
uint8_t errorPosSensorTraseiro;
uint8_t errorNegSensorTraseiro;
uint8_t errorPosSensorUmidade;
uint8_t errorNegSensorUmidade;

void SRV_ADT7410_multiplex_on(Sensor_e address)
{
   switch(address)
   {
       case SENSOR_S1:
           CTRL_1_SetHigh();
           CTRL_2_SetLow();
           CTRL_3_SetLow();           
           break;
       case SENSOR_S2:
           CTRL_1_SetLow();
           CTRL_2_SetHigh();
           CTRL_3_SetLow();          
           break;
       case SENSOR_S3:
           CTRL_1_SetLow();
           CTRL_2_SetLow();
           CTRL_3_SetHigh();         
           break;    
   }
}


void SRV_ADT7410_multiplex_off(void)
{
     
    CTRL_1_SetLow();
    CTRL_2_SetLow();
    CTRL_3_SetLow(); 
}

void  SRV_ADT7410_Init(void)
{   
    CTRL_1_SetLow();
    CTRL_2_SetLow();
    CTRL_3_SetLow();
   // SelectEEPROM_SetLow();
    SRES_SetHigh();
    
    Sensor1.CELSIUS = 0;
    Sensor2.CELSIUS = 0;
    Sensor3.CELSIUS = 0;
    
    Sensor1.FAHRENHEIT = 0;
    Sensor2.FAHRENHEIT = 0;
    Sensor3.FAHRENHEIT = 0;
    
    errorPosSensorDianteiro = 0;
    errorNegSensorDianteiro = 0;
    errorPosSensorTraseiro = 0;
    errorNegSensorTraseiro = 0;
    errorPosSensorUmidade = 0;
    errorNegSensorUmidade = 0;
    
    int y;
    for (y = 0; y < 25; y++) {
        SRV_ADT7410_ReadMeanSensor(SENSOR_S1,FAHRENHEIT,&Sensor1.FAHRENHEIT);
        SRV_ADT7410_ReadMeanSensor(SENSOR_S2,FAHRENHEIT,&Sensor2.FAHRENHEIT);
        SRV_ADT7410_ReadMeanSensor(SENSOR_S3,FAHRENHEIT,&Sensor3.FAHRENHEIT); 
        SRV_ADT7410_ReadMeanSensor(SENSOR_S1,CELSIUS,&Sensor1.CELSIUS);
        SRV_ADT7410_ReadMeanSensor(SENSOR_S2,CELSIUS,&Sensor2.CELSIUS);
        SRV_ADT7410_ReadMeanSensor(SENSOR_S3,CELSIUS,&Sensor3.CELSIUS); 

    }

}

void SRV_ADT7410_On(void)
{
    SRES_SetHigh();
}

void SRV_ADT7410_Off(void)
{
    SRES_SetLow(); 
}

void SRV_ADT7410_SetErrorSensor(Sensor_e sensor, uint8_t error_pos, uint8_t error_neg)
{
    if(sensor == SENSOR_S1)
    {
        errorPosSensorDianteiro = error_pos;
        errorNegSensorDianteiro = error_neg;
        
    }
    else if(sensor == SENSOR_S2)
    {
        errorPosSensorTraseiro = error_pos;
        errorNegSensorTraseiro = error_neg;
    }
    else if(sensor == SENSOR_S3)
    {
        errorPosSensorUmidade = error_pos;
        errorNegSensorUmidade = error_neg;
    }
}

static uint16_t SRV_ADT7410_Read(Sensor_e address)
{  
    uint8_t data[2] = {0}; 
    uint16_t temp = 0;
 
    SRV_ADT7410_multiplex_on(address);

    DRV_ADT7410_Read(0x48, 0x00, data, 2);

    temp = (uint16_t)((uint16_t)(data[0]) << 8);
    temp = (temp | data[1]); 

    SRV_ADT7410_multiplex_off();  
    
    return temp;
}

void SRV_ADT7410_ReadMeanSensor(Sensor_e address,TypeRead_e typeRead , float *value)
{    
    #define MEAN_SIZE 50
    uint32_t valueAux = 0;
    uint16_t valueMean = 0;
    
    static uint16_t meanDianteiro[MEAN_SIZE] = {0}; // vetor do mesmo tamanho do buffer da media;
    static uint16_t meanTraseiro[MEAN_SIZE] = {0}; // vetor do mesmo tamanho do buffer da media;
    static uint16_t meanUmidade[MEAN_SIZE] = {0}; // vetor do mesmo tamanho do buffer da media;
    
    static uint8_t accumulatedDianteiro = 0;
    static uint8_t accumulatedTraseiro = 0;
    static uint8_t accumulatedUmidade = 0;
    
    uint8_t index = 0;
    
    uint16_t temp = SRV_ADT7410_Read(address);

    if(temp) 
    {
        if(address == SENSOR_S1)
        {
            meanDianteiro[accumulatedDianteiro] = temp;
            accumulatedDianteiro++;
            if(accumulatedDianteiro >= MEAN_SIZE)
                accumulatedDianteiro = 0;

            for (index = 0; index < MEAN_SIZE; index++) 
            {
                valueAux = valueAux + meanDianteiro[index];
            }
            
            valueMean = (uint16_t)(valueAux / MEAN_SIZE);
            valueAux = 0;

            *value = (float)(((float)valueMean + errorPosSensorDianteiro - errorNegSensorDianteiro) / 128.0f);            

            if(typeRead == 1){*value = 1.8 * *value + 32;}
        }
        else if(address == SENSOR_S2)
        {
            meanTraseiro[accumulatedTraseiro] = temp;
            accumulatedTraseiro++;
            if(accumulatedTraseiro >= MEAN_SIZE)
                accumulatedTraseiro = 0;

            for (index = 0; index < MEAN_SIZE; index++) 
            {
                valueAux = valueAux + meanTraseiro[index];
            }
            
            valueMean = (uint16_t)(valueAux / MEAN_SIZE);
            valueAux = 0;

            *value = (float)(((float)valueMean + errorPosSensorTraseiro - errorNegSensorTraseiro) / 128.0f);           

            if(typeRead == 1){*value = 1.8 * *value + 32;}
        }
        else if(address == SENSOR_S3)
        {
            meanUmidade[accumulatedUmidade] = temp;
            accumulatedUmidade++;
            if(accumulatedUmidade >= MEAN_SIZE)
                accumulatedUmidade = 0;

            for (index = 0; index < MEAN_SIZE; index++) 
            {
                valueAux = valueAux + meanUmidade[index];
            }
            
            valueMean = (uint16_t)(valueAux / MEAN_SIZE);
            valueAux = 0;

            *value = (float)(((float)valueMean + errorPosSensorUmidade - errorNegSensorUmidade) / 128.0f);            

            if(typeRead == 1){*value = 1.8 * *value + 32;}
        }
    }
    else
    {       
        *value = 0;        
    }
}

void SRV_ADT7410_Run(void)
{
    static uint32_t tick = 0;
	static uint32_t tickLast = 0;
    
    static uint16_t timeReset = 0;
    
	tick = SRV_TIMER_GetTick();
    
	if((uint32_t)(tick - tickLast) >= 250)
	{
        tickLast = tick;
        
        timeReset++;  
        
        if(timeReset <= 240)
        {     
            SRV_ADT7410_ReadMeanSensor(SENSOR_S1,FAHRENHEIT,&Sensor1.FAHRENHEIT);
            SRV_ADT7410_ReadMeanSensor(SENSOR_S2,FAHRENHEIT,&Sensor2.FAHRENHEIT);
            SRV_ADT7410_ReadMeanSensor(SENSOR_S3,FAHRENHEIT,&Sensor3.FAHRENHEIT); 
            SRV_ADT7410_ReadMeanSensor(SENSOR_S1,CELSIUS,&Sensor1.CELSIUS);
            SRV_ADT7410_ReadMeanSensor(SENSOR_S2,CELSIUS,&Sensor2.CELSIUS);
            SRV_ADT7410_ReadMeanSensor(SENSOR_S3,CELSIUS,&Sensor3.CELSIUS); 
        }
        if(timeReset == 241)
        {
           SRV_ADT7410_Off(); 
        }
        if(timeReset >= 245)
        {
           SRV_ADT7410_On(); 
           timeReset = 0;
        }
    }
}

float SRV_ADT7410_GetTemperature(Sensor_e sensor ,TypeRead_e typeRead )
{
    if(sensor == SENSOR_S1)
    {
        if(typeRead == CELSIUS){   
            return Sensor1.CELSIUS;  
        }
        else{      
           return Sensor1.FAHRENHEIT;  
        }        
    }
    else if(sensor == SENSOR_S2)
    {
        if(typeRead == CELSIUS){           
            return Sensor2.CELSIUS;  
        }
        else{     
           return Sensor2.FAHRENHEIT;  
        }              
    }
    else if(sensor == SENSOR_S3)
    {
        if(typeRead == CELSIUS){          
            return Sensor3.CELSIUS;  
        }
        else{          
           return Sensor3.FAHRENHEIT;  
        }             
    }   
    return 0;
}


