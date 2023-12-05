/* 
 * File:   Utilities.h
 * Author: flavio.luciano
 *
 * Created on September 7, 2020, 11:59 AM
 */

#ifndef UTILITIES_H
#define	UTILITIES_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "Convert.h"


typedef enum
{
  HOME,
  MenuAjusteErro,
} Estado_e;


typedef enum{
    T1 = 0,
    T2,
    T3,
    T4,
    T5,
    T6,
    T7,
    NenhumaTecla,
}Key_e;

typedef enum {
    CELSIUS = 0,
    FAHRENHEIT
} TypeRead_e;

typedef enum {
    SENSOR_S1 = 1,
    SENSOR_S2,
    SENSOR_S3,
} Sensor_e;

typedef struct {
    uint8_t tela[4][20];
} Display_t;


typedef union {

    struct {
        char pos1 : 8;
        char pos2 : 8;
        char pos3 : 8;
        char pos4 : 8;
        char pos5 : 8;
        char pos6 : 8;
        char pos7 : 8;
    };
    char value[7];
} Version_t;

typedef union {

    struct {
        char pos1 : 8;
        char pos2 : 8;
        char pos3 : 8;
        char pos4 : 8;
        char pos5 : 8;
    };
    char value[5];
} Temperature_t;

typedef union {

    struct {
        char digito1 : 8;
        char digito2 : 8;
        char digito3 : 8;
    };
    char value[3];
} ErroPositivo_t;

typedef union {

    struct {
        char digito1 : 8;
        char digito2 : 8;
        char digito3 : 8;
    };
    char value[3];
} ErroNegativo_t;

typedef struct {
    uint8_t negativo;
    uint8_t positivo;
} ErrorSensort_t;


typedef struct {
    uint8_t value[1];
} Senha_t;

typedef struct {
    float temperatureS1;
    float temperatureS2;
    float temperatureS3;
    uint16_t DD;
    uint16_t DT;
    uint16_t CO2;
    
    ErrorSensort_t erroSensorS1;
    ErrorSensort_t erroSensorS2;
    ErrorSensort_t erroSensorS3;
    
    uint16_t contWDT;
    bool ResetWDT;
    
    Version_t version;  
    uint8_t senha;
} Object_t;

bool habilitaRefrescamento = false;


typedef void (*ptrFunction)(Object_t* objetoHTAD);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UTILITIES_H */

