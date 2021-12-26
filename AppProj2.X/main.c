/* 
 * File: main.c
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 

#include "xc.h"
#include "IOs.h"
#include "TimeDelay.h"
#include "UART2.h"
#include "ChangeClk.h"
#include "ADC.h"

int main(void)
{
    IOinit();       //setup GPIO
    T2Init();       //setup Timer 2     
    ADCInit();      //set up ADC values
    while(1)
    {
        Sleep();     //Sleep state
    }
    
    return 0;
}
