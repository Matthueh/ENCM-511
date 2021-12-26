#include <xc.h>
#include <p24F16KA101.h>

void main(void){
    
    TRISAbits.TRISA0 = 1; //Sets RA0-GPIO2 as input
    TRISAbits.TRISA1 = 1; //Sets RA1-GPIO3 as input
    TRISAbits.TRISA2 = 1; //Sets RA2-GPIO4 as input
    TRISAbits.TRISA4 = 1; //Sets RA4-GPIO5 as input. 

    
    TRISBbits.TRISB0 = 0; //sets RB0-GPIO6 as output
    TRISBbits.TRISB1 = 0; //sets RB1-GPIO7 as output
    TRISBbits.TRISB2 = 0; //sets RB2-GPIO8 as output
    TRISBbits.TRISB4 = 0; //sets RB4-GPIO9 as output
    TRISBbits.TRISB7 = 0; //sets RB7-GPIO10 as output
    TRISBbits.TRISB8 = 0; //sets RB8-GPIO11 as output
    TRISBbits.TRISB9 = 0; //sets RB9-GPIO12 as output
    TRISBbits.TRISB12 = 0;//sets RB12-GPIO13 as output
    
    //UCID: 30052684
    while(1)//This is to keep it running.
    {    
        //This displays nothing.
        if((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 0)
                            && (PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 0))
        {
            LATBbits.LATB0 = 0; //Sets RB0 LED off
            LATBbits.LATB1 = 0; //Sets RB1 LED off
            LATBbits.LATB2 = 0; //Sets RB2 LED off
            LATBbits.LATB4 = 0; //Sets RB4 LED off
            LATBbits.LATB7 = 0; //Sets RB7 LED off
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off
        }
        //This displays the first number in the u of c id, which is 3.
        else if((PORTAbits.RA0 == 1) && (PORTAbits.RA1 == 0) 
                            && (PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 0))
        {
            LATBbits.LATB0 = 1; //Sets RB0 LED on
            LATBbits.LATB1 = 1; //Sets RB1 LED on
            LATBbits.LATB2 = 1; //Sets RB2 LED on
            LATBbits.LATB4 = 0; //Sets RB4 LED off
            LATBbits.LATB7 = 0; //Sets RB7 LED off
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off
        }
        //This displays the second number in the u of c id, which is 0.
        else if((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 1) 
                                && (PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 0))
        {
            LATBbits.LATB0 = 0; //Sets RB0 LED off
            LATBbits.LATB1 = 0; //Sets RB1 LED off
            LATBbits.LATB2 = 0; //Sets RB2 LED off
            LATBbits.LATB4 = 0; //Sets RB4 LED off
            LATBbits.LATB7 = 0; //Sets RB7 LED off
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off
        }
        //This displays the third number in the u of c id, which is 0.
        else if((PORTAbits.RA0 == 1) && (PORTAbits.RA1 == 1) 
                                && (PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 0))
        {
            LATBbits.LATB0 = 0; //Sets RB0 LED off
            LATBbits.LATB1 = 0; //Sets RB1 LED off
            LATBbits.LATB2 = 0; //Sets RB2 LED off
            LATBbits.LATB4 = 0; //Sets RB4 LED off
            LATBbits.LATB7 = 0; //Sets RB7 LED off
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off
        }
        //This displays the fourth number in the u of c id, which is 5.
        else if((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 0) 
                                && (PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 0))
        {
            LATBbits.LATB0 = 1; //Sets RB0 LED on
            LATBbits.LATB1 = 1; //Sets RB1 LED on
            LATBbits.LATB2 = 1; //Sets RB2 LED on
            LATBbits.LATB4 = 1; //Sets RB4 LED on
            LATBbits.LATB7 = 1; //Sets RB7 LED on
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off
        }
        //This displays the fifth number in the u of c id, which is 2.
        else if((PORTAbits.RA0 == 1) && (PORTAbits.RA1 == 0) 
                                && (PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 0))
        {
            LATBbits.LATB0 = 1; //Sets RB0 LED on
            LATBbits.LATB1 = 1; //Sets RB1 LED on
            LATBbits.LATB2 = 0; //Sets RB2 LED off
            LATBbits.LATB4 = 0; //Sets RB4 LED off
            LATBbits.LATB7 = 0; //Sets RB7 LED off
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off
        }
        //This displays the sixth number in the u of c id, which is 6.
        else if((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 1) 
                            && (PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 0))
        {
            LATBbits.LATB0 = 1; //Sets RB0 LED on
            LATBbits.LATB1 = 1; //Sets RB1 LED on
            LATBbits.LATB2 = 1; //Sets RB2 LED on
            LATBbits.LATB4 = 1; //Sets RB4 LED on
            LATBbits.LATB7 = 1; //Sets RB7 LED on
            LATBbits.LATB8 = 1; //Sets RB8 LED on
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off
 
        }
        //This displays the seventh number in the u of c id, which is 8.
        else if((PORTAbits.RA0 == 1) && (PORTAbits.RA1 == 1) 
                            && (PORTAbits.RA2 == 1) && (PORTAbits.RA4 == 0))
        {     
            LATBbits.LATB0 = 1; //Sets RB0 LED on
            LATBbits.LATB1 = 1; //Sets RB1 LED on
            LATBbits.LATB2 = 1; //Sets RB2 LED on
            LATBbits.LATB4 = 1; //Sets RB4 LED on
            LATBbits.LATB7 = 1; //Sets RB7 LED on
            LATBbits.LATB8 = 1; //Sets RB8 LED on
            LATBbits.LATB9 = 1; //Sets RB9 LED on
            LATBbits.LATB12 = 1;//Sets RB12 LED on
        }
        //This displays the eighth number in the u of c id, which is 4. Last number.
        else if((PORTAbits.RA0 == 0) && (PORTAbits.RA1 == 0) 
                               && (PORTAbits.RA2 == 0) && (PORTAbits.RA4 == 1))
        {
            LATBbits.LATB0 = 1; //Sets RB0 LED on
            LATBbits.LATB1 = 1; //Sets RB1 LED on
            LATBbits.LATB2 = 1; //Sets RB2 LED on
            LATBbits.LATB4 = 1; //Sets RB4 LED on
            LATBbits.LATB7 = 0; //Sets RB7 LED off
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off 
        }
        //Everything else from 1001 -1111 will be defaulted to 0 output.
        else{ 
            LATBbits.LATB0 = 0; //Sets RB0 LED off
            LATBbits.LATB1 = 0; //Sets RB1 LED off
            LATBbits.LATB2 = 0; //Sets RB2 LED off
            LATBbits.LATB4 = 0; //Sets RB4 LED off
            LATBbits.LATB7 = 0; //Sets RB7 LED off
            LATBbits.LATB8 = 0; //Sets RB8 LED off
            LATBbits.LATB9 = 0; //Sets RB9 LED off
            LATBbits.LATB12 = 0;//Sets RB12 LED off 
        }
    }
}
