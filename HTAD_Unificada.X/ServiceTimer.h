/* 
 * File:   ServiceTimer.h
 * Author: flavio.luciano
 *
 * Created on September 14, 2020, 11:46 AM
 */

#ifndef SERVICETIMER_H
#define	SERVICETIMER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void SRV_TIMER_Init(void);
    void SRV_TIMER_Run(void);
    void SRV_TIMER_TickInterrupt(void);
    uint32_t SRV_TIMER_GetTick(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVICETIMER_H */

