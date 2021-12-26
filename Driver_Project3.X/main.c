/* 
 * File: main.c
 * Author: Jonathan Chong
 * 
*/ 
#include <xc.h>
#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>


// User header files
#include "IOs.h"
#include "ChangeClk.h"
#include "TimeDelay.h"
#include "UART2.h"





//Global Variables
uint8_t PBFlag;

//MAIN
int main(void) {
     
    // Change Clock
    //NewClk(32); //change clock to 32kHz for lowest power consumption
    IOinit();   //initialize IOs
    
    while(1)
    {
        IOCheck();
    }
    return 0;
}
