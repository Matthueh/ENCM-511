/* 
 * File: IOs.h
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 


#include <xc.h> // include processor files - each processor file is guarded.  
#include "TimeDelay.h"
#include "UART2.h"


#ifndef GPIO_H
#define GPIO_H

void IOinit (void);         

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);


#endif