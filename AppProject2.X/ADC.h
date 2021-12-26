/* 
 * File: ADC.h
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 

#include <xc.h> // include processor files - each processor file is guarded.  

#ifndef ADC_H

#define	ADC_H
void  ADCInit(void);

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);

void DisplayVoltmeter(void);
void DisplayOhmmeter(void);
void DisplayCapacitance(void);



#endif	/* ADC_H */

