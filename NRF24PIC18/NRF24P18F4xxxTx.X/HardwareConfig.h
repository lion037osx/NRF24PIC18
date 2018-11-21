/* 
 * File:   HardwareConfig.h
 * Author: optimus
 *
 * Created on November 16, 2018, 1:29 AM
 */

#ifndef HARDWARECONFIG_H
#define	HARDWARECONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

//#define __MODE_RX__
#define __MODE_TX__    
    
#if defined (__MODE_RX__)
    #define __PIC18F4520__        
#endif
             
#if defined (__MODE_TX__)
    #define __PIC18F4620__
#endif
#ifdef	__cplusplus
}
#endif
#endif	/* HARDWARECONFIG_H */

