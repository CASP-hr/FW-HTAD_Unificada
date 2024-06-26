/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set DPD aliases
#define DPD_TRIS                 TRISAbits.TRISA0
#define DPD_LAT                  LATAbits.LATA0
#define DPD_PORT                 PORTAbits.RA0
#define DPD_ANS                  ANSELAbits.ANSA0
#define DPD_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define DPD_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define DPD_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define DPD_GetValue()           PORTAbits.RA0
#define DPD_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define DPD_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define DPD_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define DPD_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set DPT aliases
#define DPT_TRIS                 TRISAbits.TRISA1
#define DPT_LAT                  LATAbits.LATA1
#define DPT_PORT                 PORTAbits.RA1
#define DPT_ANS                  ANSELAbits.ANSA1
#define DPT_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DPT_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DPT_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DPT_GetValue()           PORTAbits.RA1
#define DPT_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DPT_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DPT_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define DPT_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set Led_State aliases
#define Led_State_TRIS                 TRISAbits.TRISA2
#define Led_State_LAT                  LATAbits.LATA2
#define Led_State_PORT                 PORTAbits.RA2
#define Led_State_ANS                  ANSELAbits.ANSA2
#define Led_State_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Led_State_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Led_State_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Led_State_GetValue()           PORTAbits.RA2
#define Led_State_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Led_State_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Led_State_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Led_State_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set CO2A aliases
#define CO2A_TRIS                 TRISAbits.TRISA3
#define CO2A_LAT                  LATAbits.LATA3
#define CO2A_PORT                 PORTAbits.RA3
#define CO2A_ANS                  ANSELAbits.ANSA3
#define CO2A_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define CO2A_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define CO2A_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define CO2A_GetValue()           PORTAbits.RA3
#define CO2A_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define CO2A_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define CO2A_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define CO2A_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set CTRL_3 aliases
#define CTRL_3_TRIS                 TRISAbits.TRISA4
#define CTRL_3_LAT                  LATAbits.LATA4
#define CTRL_3_PORT                 PORTAbits.RA4
#define CTRL_3_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define CTRL_3_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define CTRL_3_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define CTRL_3_GetValue()           PORTAbits.RA4
#define CTRL_3_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define CTRL_3_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set SRES aliases
#define SRES_TRIS                 TRISAbits.TRISA5
#define SRES_LAT                  LATAbits.LATA5
#define SRES_PORT                 PORTAbits.RA5
#define SRES_ANS                  ANSELAbits.ANSA5
#define SRES_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SRES_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SRES_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SRES_GetValue()           PORTAbits.RA5
#define SRES_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SRES_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SRES_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define SRES_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set D0 aliases
#define D0_TRIS                 TRISBbits.TRISB0
#define D0_LAT                  LATBbits.LATB0
#define D0_PORT                 PORTBbits.RB0
#define D0_WPU                  WPUBbits.WPUB0
#define D0_ANS                  ANSELBbits.ANSB0
#define D0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define D0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define D0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define D0_GetValue()           PORTBbits.RB0
#define D0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define D0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define D0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define D0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define D0_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define D0_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set D1 aliases
#define D1_TRIS                 TRISBbits.TRISB1
#define D1_LAT                  LATBbits.LATB1
#define D1_PORT                 PORTBbits.RB1
#define D1_WPU                  WPUBbits.WPUB1
#define D1_ANS                  ANSELBbits.ANSB1
#define D1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define D1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define D1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define D1_GetValue()           PORTBbits.RB1
#define D1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define D1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define D1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define D1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define D1_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define D1_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set D2 aliases
#define D2_TRIS                 TRISBbits.TRISB2
#define D2_LAT                  LATBbits.LATB2
#define D2_PORT                 PORTBbits.RB2
#define D2_WPU                  WPUBbits.WPUB2
#define D2_ANS                  ANSELBbits.ANSB2
#define D2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define D2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define D2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define D2_GetValue()           PORTBbits.RB2
#define D2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define D2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define D2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define D2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define D2_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define D2_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set D3 aliases
#define D3_TRIS                 TRISBbits.TRISB3
#define D3_LAT                  LATBbits.LATB3
#define D3_PORT                 PORTBbits.RB3
#define D3_WPU                  WPUBbits.WPUB3
#define D3_ANS                  ANSELBbits.ANSB3
#define D3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define D3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define D3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define D3_GetValue()           PORTBbits.RB3
#define D3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define D3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define D3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define D3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define D3_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define D3_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set RS aliases
#define RS_TRIS                 TRISBbits.TRISB4
#define RS_LAT                  LATBbits.LATB4
#define RS_PORT                 PORTBbits.RB4
#define RS_WPU                  WPUBbits.WPUB4
#define RS_ANS                  ANSELBbits.ANSB4
#define RS_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RS_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RS_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RS_GetValue()           PORTBbits.RB4
#define RS_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RS_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RS_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define RS_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define RS_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define RS_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set EN aliases
#define EN_TRIS                 TRISBbits.TRISB5
#define EN_LAT                  LATBbits.LATB5
#define EN_PORT                 PORTBbits.RB5
#define EN_WPU                  WPUBbits.WPUB5
#define EN_ANS                  ANSELBbits.ANSB5
#define EN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define EN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define EN_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define EN_GetValue()           PORTBbits.RB5
#define EN_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define EN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define EN_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define EN_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define EN_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define EN_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set CTRL_2 aliases
#define CTRL_2_TRIS                 TRISBbits.TRISB6
#define CTRL_2_LAT                  LATBbits.LATB6
#define CTRL_2_PORT                 PORTBbits.RB6
#define CTRL_2_WPU                  WPUBbits.WPUB6
#define CTRL_2_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define CTRL_2_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define CTRL_2_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define CTRL_2_GetValue()           PORTBbits.RB6
#define CTRL_2_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define CTRL_2_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define CTRL_2_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define CTRL_2_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set CTRL_1 aliases
#define CTRL_1_TRIS                 TRISBbits.TRISB7
#define CTRL_1_LAT                  LATBbits.LATB7
#define CTRL_1_PORT                 PORTBbits.RB7
#define CTRL_1_WPU                  WPUBbits.WPUB7
#define CTRL_1_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define CTRL_1_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define CTRL_1_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define CTRL_1_GetValue()           PORTBbits.RB7
#define CTRL_1_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define CTRL_1_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define CTRL_1_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define CTRL_1_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set TE0 aliases
#define TE0_TRIS                 TRISCbits.TRISC0
#define TE0_LAT                  LATCbits.LATC0
#define TE0_PORT                 PORTCbits.RC0
#define TE0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define TE0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define TE0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define TE0_GetValue()           PORTCbits.RC0
#define TE0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define TE0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set TE1 aliases
#define TE1_TRIS                 TRISCbits.TRISC1
#define TE1_LAT                  LATCbits.LATC1
#define TE1_PORT                 PORTCbits.RC1
#define TE1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define TE1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define TE1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define TE1_GetValue()           PORTCbits.RC1
#define TE1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define TE1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set TE2 aliases
#define TE2_TRIS                 TRISCbits.TRISC2
#define TE2_LAT                  LATCbits.LATC2
#define TE2_PORT                 PORTCbits.RC2
#define TE2_ANS                  ANSELCbits.ANSC2
#define TE2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define TE2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define TE2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define TE2_GetValue()           PORTCbits.RC2
#define TE2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define TE2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define TE2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define TE2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set TX_Enable aliases
#define TX_Enable_TRIS                 TRISCbits.TRISC5
#define TX_Enable_LAT                  LATCbits.LATC5
#define TX_Enable_PORT                 PORTCbits.RC5
#define TX_Enable_ANS                  ANSELCbits.ANSC5
#define TX_Enable_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define TX_Enable_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define TX_Enable_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define TX_Enable_GetValue()           PORTCbits.RC5
#define TX_Enable_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define TX_Enable_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define TX_Enable_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define TX_Enable_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/