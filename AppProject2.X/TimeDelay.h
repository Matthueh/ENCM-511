/* 
 * File: TimeDelay.h
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 
#include <xc.h> // include processor files - each processor file is guarded. 

#ifndef TIMERS_H
#define TIMERS_H

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);


void T2Init(void);
void timer(void);


#endif