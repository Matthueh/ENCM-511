
/* 
 * File: ADC.c
 * Author: Jonathan Chong, Matthew Ho, Alexander Sembrat
 * 
 * 
*/ 
#include "xc.h"
#include "ADC.h"
#include "UART2.h"
#include "string.h"
#include "stdio.h"
#include "TimeDelay.h"
// ADC initialization: call before using do_ADC() and do_ADCseq()
// Sets up ADC on pin8/RA3/AN5

extern int stop = 0;            //Global variable for Capacitance equation

void  ADCInit(void)
{

    AD1CON1bits.ADON = 1; // turn on ADC module
    AD1CON1bits.ADSIDL= 0; // continue ADC operation in idle mode
    AD1CON1bits.FORM = 0b00; //ob00: Int, 01: Signed Int, 10: Fractional, 11: Signed fract
    AD1CON1bits.SSRC = 0b111; //Start ADC conversion TIme set by SAMC has passed
    AD1CON1bits.ASAM = 0; // Next Sampling begin when SAMP bit is set
    AD1CON1bits.SAMP =0; // Set this bit ADC routine to start sampling

    //sampling time and ADC clk select
    AD1CON2bits.VCFG = 0b000; // Selects AVDD+=AVDD, AVSS (supply voltage to PIC) Vref -= AVSS
    AD1CON2bits.CSCNA =0; // Do not scan inputs: use channel selected by CH0SA bits
    AD1CON2bits.SMPI =0b0000; //Any ADC interrupts occur at completion of each sample/convert seq
    AD1CON2bits.BUFM =0; //Buffer configured as 1 16 word buffer
    AD1CON2bits.ALTS=0;  //Always use zMUXA input MUX settings
    AD1CON3bits.ADRC = 0; //0: Use system clock; 1: ADC uses internal RC clock for idle or sleep mode
    AD1CON3bits.SAMC=0b11111; //Sample time = 31*TAD = 31*1/125e3
    AD1CON3bits.ADCS =0b00111111; //ADCS conversion clock select bits 64 Tcy. Ignored if using AD RC clock


    //IINT bit setup
    IPC3bits.AD1IP = 7;

return;
//Configure the ADC?s sample time by setting bits in AD1CON3 shown in slide 17
// Ensure sample time is 1/10th of signal being sampled
// Select and configure ADC input as shown in slides 18-20
/* ------------- ADC SAMPLING AND CONVERSION ------------------*/

/*AD1CON1bits.SAMP=1; //Start Sampling, Conversion starts automatically after SSRC and SAMC settings
while(AD1CON1bits.DONE==0)
{}
ADCvalue = ADC1BUF0; // ADC output is stored in ADC1BUF0 as this point
AD1CON1bits.SAMP=0; //Stop sampling
AD1CON1bits.ADON=0; //Turn off ADC, ADC value stored in ADC1BUF0;
return (ADCvalue); //returns 10 bit ADC output stored in ADC1BIF0 to calling function*/
}

//ADC conversion subroutine
//Returns Single conversion 10bits ABC value (ADCvalue) in unsigned int form
unsigned int do_ADC(void)
{
    unsigned int ADCvalue = 0;
    AD1CON1bits.SAMP = 1;       //start sampling, conversion starts automatically after SSRC and SAMC settings
    while(AD1CON1bits.DONE==0)
    {
    }   
    AD1CON1bits.SAMP=0;         // stop sampling
    AD1CON1bits.ADON = 0;       //Turn off ADC module
    ADCvalue = ADC1BUF0;        //save value from register
    return (ADCvalue);          //return that value
}

void DisplayVoltmeter()
{ 
    AD1CON1bits.ADON = 1;           //Turn on ADC module
    AD1CHSbits.CH0NB = 0;         
    AD1CHSbits.CH0SB = 0b0101;      //Positive input is AN5/RA3/pins for MUXB
    AD1CHSbits.CH0NA = 0;         
    AD1CHSbits.CH0SA = 0b0101;      //Positive input is AN5/RA3/pins for MUXA
    uint16_t voltage;               //variable to store ADCBUFO value
    voltage = do_ADC();             //Does ADC conversion on AN5/I08
    

    
    char str[6];                            //Create string to hold value
    double volts = (voltage *3.25)/1024;    //Convert ADC value to voltage
    sprintf(str, "%1.3f", volts);           //put in string
    Disp2String("VOLTMETER Voltage = ");    //Display message
    Disp2String(str);                       //Display voltage value
    XmitUART2(' ',1);                       //Space
    XmitUART2('V', 1);                      //Unit Volts
    
    return;
}
void DisplayOhmmeter()
{
    AD1CON1bits.ADON = 1;           //Turn on ADC module
    AD1CHSbits.CH0NB = 0;           
    AD1CHSbits.CH0SB = 0b1011;      //Positive input is AN11/RB13/pins for MUXB
    AD1CHSbits.CH0NA = 0;          
    AD1CHSbits.CH0SA = 0b1011;      //Positive input is AN11/RB13/pins for MUXA
    uint16_t voltage;               //variable to store ADCBUFO value
    voltage = do_ADC();             //DOes ADC conversion onAN5/I08
    

    
    char str[6];                                        //Create string to put resistance value in
    double volts = (voltage *3.25)/1024;                //Convert ADC value to voltage
    double resistance = (volts*1000)/(3.25-volts);      //Use that voltage to in formula for resistance
    sprintf(str, "%1.3f", resistance);                  //Convert resistance to string
    Disp2String("OHMMETER Resistance = ");              //Display message
    Disp2String(str);                                   //Display resistance value
    XmitUART2(' ',1);                                   //Space
    XmitUART2(234, 1);                                  //Display Ohm symbol
    
}

void DisplayCapacitance()
{
    
    AD1CON1bits.ADON = 1;           //Turn on ADC module
    AD1CHSbits.CH0NB = 0;           
    AD1CHSbits.CH0SB = 0b1100;      //Positive input is AN12/RB12/pins for MUXB
    AD1CHSbits.CH0NA = 0;           
    AD1CHSbits.CH0SA = 0b1100;      //Positive input is AN12/RB12/pins for MUXA
    
    timer();                        //call function to start timer
    LATBbits.LATB7 = 1;             //Start charging Capacitor through resistor
    
    uint16_t voltage;               //variable to hold ADC value
    
    
    voltage = do_ADC();              //Call do_ADC and save value to voltage
    double volts = (voltage *3.25)/1024;    // Convert adcvoltage to volts
    
    
    if (volts >= 2.054)                     //if voltage is 63.2% of max voltage
    {
        
        
        T2CONbits.TON = 0;                  //Turn off timer
        LATBbits.LATB7 = 0;                 //Turn off voltage
        double time = TMR2;                 //Save TMR2 value as Tau
        TMR2 = 0;                           //Zero Timer2

        double Capacitance = time/10000;    //Do formula for Capacitance (C = T/R)

        

        char str[10];                       //Create String for Cap value
        if (stop == 0)                      //If stop is 0 then do message - ensures it isn't repeating
        {
            sprintf(str, "%1.4f", Capacitance);     //Put Cap value in String
            Disp2String("Capacitance = ");          //Display Message
            Disp2String(str);                       //Display cap value
            XmitUART2(' ',1);                       //Space
            Disp2String("uF");                      //Display units uF
        }
        stop = 1;                                   //Stop = 1 to ensure it takes first value
    }
    
}


void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; // Clear the ADC1 Interrupt Flag
}
