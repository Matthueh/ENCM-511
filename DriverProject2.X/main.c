/* 
 * File:   main.c
 * Authors: Alexander Sembrat, Matthew Ho, Jonathan Chong
 * ENCM 511 Driver Project 2
 * Created on October 15
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "TimeDelay.h"
#include "IOs.h"
/*
 * 
 */
int main() {
    
    IOinit(); //call to initialize ports
    
    while(1){
        IOcheck(); //call to check ports and decide what to do
    }
    
    return 0;
}

