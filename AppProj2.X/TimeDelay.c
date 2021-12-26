/* 
 * File: TimeDelay.c
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 

#include "xc.h"
#include "TimeDelay.h"
#include "ChangeClk.h"
#include "UART2.h"



void T2Init(void)
{
    //T2CON config
    T2CONbits.TSIDL = 0; //operate in idle mode
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    T2CONbits.TCS = 0; // use internal clock
    // T2CONbits.TGATE = 0;
    
    //T2CON prescaler select
    T2CONbits.TCKPS0 = 0;
    T2CONbits.TCKPS1 = 1;
    
    
    // Timer 2 interrupt config
    IPC1bits.T2IP = 3;  //7 is highest and 1 is lowest priority
    IEC0bits.T2IE = 1;  //enable timer interrupt
    IFS0bits.T2IF = 0;  // Clear timer 2 flag
    
    return;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;              //Clear T2 Interrupt Flag
    return;
}

void timer(void)
{
    if (T2CONbits.TON == 0){
        //PR2 = 65535;            //max PR2
        TMR2 = 0;               //zero timer2 register at start
        T2CONbits.TON = 1;      //start timer
    }
    return;
}