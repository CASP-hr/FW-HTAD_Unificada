/* 
 * File:   App_HTAD.h
 * Author: flavio.luciano
 *
 * Created on July 20, 2023, 11:16 AM
 */

#ifndef APP_HTAD_H
#define	APP_HTAD_H

#include "Utilities.h"

void App_HTAD_init();
void App_HTAD_run();

Key_e readKeypad();

void App_HTAD_Home(Object_t* objetoHTAD);
void App_HTAD_MenuAjusteErro(Object_t* objetoHTAD);
void App_HTAD_UpdateDIrectNet(void);

void App_HTAD_ClearWDT(void);

#endif	/* APP_HTAD_H */

