/* 
 * File: ChangeClk.c
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 

#include "xc.h"
#include "ChangeClk.h"

void NewClk(unsigned int clkval) {
    //char COSC = OSCCONbits.COSC;
    char COSCNOSC;
    if(clkval == 8)
    {
        COSCNOSC = 0x00;
    }
    else if (clkval == 500)
    {
        COSCNOSC = 0x66;
    }
    else if (clkval == 31)
    {
        COSCNOSC = 0x55;
    }
    else
    {
        COSCNOSC = 0;
    }
    SRbits.IPL = 7;
    __builtin_write_OSCCONH(COSCNOSC);
    __builtin_write_OSCCONL(0x01);
    OSCCONbits.OSWEN = 1;
    while(OSCCONbits.OSWEN == 1)
    {
    }
    SRbits.IPL = 0;
    return;
}