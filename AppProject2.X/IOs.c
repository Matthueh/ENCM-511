/* 
 * File: IOs.c
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 

#include "xc.h"
#include "UART2.h"
#include "TimeDelay.h"
#include "IOs.h"
#include "ChangeClk.h"
#include "ADC.h"


/*Function IOinit()
 
 This function initiates all GPIO input and outputs
 It also sets up the CN interupts on the respective inputs*/
void IOinit(void)
{
    
    AD1PCFG = 0xFFFF;       // Turn all analog pins as digital
    TRISAbits.TRISA4 = 1;   //Sets RA4 as input (Pushbutton)
    TRISBbits.TRISB4 = 1;   //Sets RB4 as input (Pushbutton)
    TRISAbits.TRISA2 = 1;   //Sets RA2 as input (Pushbutton)
    TRISBbits.TRISB8 = 0;   //Sets RB8 as output (LED)
    TRISBbits.TRISB7 = 0;   //Set as output for RC circuit
    
    CNPU1bits.CN0PUE = 1;   //Pull CN0 - RA4 up (RA4 pushbutton active low)
    CNPU1bits.CN1PUE = 1;   //Pull CN1 - RB4 up (RB4 pushbutton active low)
    CNPU2bits.CN30PUE = 1;  //Pull CN30 - RA2 up (RA2 pushbutton active low)
    
    CNEN1bits.CN0IE = 1;    //Enable CN0 interrupt
    CNEN1bits.CN1IE = 1;    //enable CN1 interrupt
    CNEN2bits.CN30IE = 1;   //enable CN30 interrupt
    IPC4bits.CNIP = 5;      //set CN interrupt priority
    IFS1bits.CNIF = 0;      //clears the CN interrupt flag
    IEC1bits.CNIE = 1;      //enable the CN interrupt (general)
    
    
    TRISAbits.TRISA3 = 1;       //Set pin8/RA3/AN5 as input
    AD1PCFGbits.PCFG5 = 0;      //Set only pin8/AN5/RA3 as ANalog input for ADC
    TRISBbits.TRISB13 = 1;      //Set pin16/RB13/AN11 as input
    AD1PCFGbits.PCFG11 = 0;     //Set only pin13/AN11/RB13 as ANalog input for ADC
    TRISBbits.TRISB12 = 1;      //Set pin16/RB12/AN12 as input
    AD1PCFGbits.PCFG12 = 0;     //Set only pin15/AN12/RB12 as ANalog input for AD
    AD1CSSL = 0; // Input Scan disabled, 0x0000 is default state.
    

    Disp2String("Nothing Pressed                    ");         //Displays text on tera term
    return;
}


/*
 This is the Interrupt Service Routine for any CN interrupt*/
void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt (void)
{
    
    if(IFS1bits.CNIF == 1)              //if CN interrupt flag...
    {
        IFS1bits.CNIF = 0;              //clears the CN interrupt flag
        
        if(PORTAbits.RA2 == 0)          //if PB1 is pressed
        {
            while(PORTAbits.RA2 == 0)       //while PB1 pressed
            {
                DisplayVoltmeter();            //This will sample, calculate and display DisplayVoltage
                
            }
        }
        else if(PORTBbits.RB4 == 0)         //If PB2 pressed
        {
            while(PORTBbits.RB4 == 0)       //While PB2 pressed
            {
                DisplayOhmmeter();             //call DispOhmmeter
            }
        }
        else if(PORTAbits.RA4 == 0)         //If PB3 pressed
        {
            extern int stop;                //declare extern variable
            stop = 0;                       //set stop to 0
            while(PORTAbits.RA4 == 0)       //while PB3 pressed
            {
                
                DisplayCapacitance();          //This will sample, calculate and display DisplayCapacitance
            }
            
        }
        else                                //Else clear and display Nothing pressed
        {
            Disp2String("Nothing Pressed                    ");
        }
    }
        
    return;
}