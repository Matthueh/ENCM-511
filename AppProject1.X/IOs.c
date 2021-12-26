/* 
 * File: IOs.c
 * Author: Jonathan Chong, Alex Sembrat, Matthew Ho
 * 
*/ 

#include "IOs.h"
#include "TimeDelay.h"
#include "UART2.h"
#include "ChangeClk.h"
#include "string.h"

int minute = 0;
int second = 0;
int state = 0;
int light = 0;
int alarm = 0;

extern uint8_t PBFlag;

void IOinit(){
    AD1PCFG = 0xFFFF; // All analog pins digital
    TRISBbits.TRISB8 = 0; //RB8: output
    TRISBbits.TRISB4 = 1;   //RB4: input
    TRISAbits.TRISA4 = 1;   //RA4: input
    TRISAbits.TRISA2 = 1;   //RA2: input
    CNPU1bits.CN0PUE = 1;   //CN0/RA4: enables pull up
    CNPU1bits.CN1PUE = 1;   //CN1/RB4: enable pull up
    CNPU2bits.CN30PUE = 1;  //CN30/RA2: enable pull up
    CNEN1bits.CN0IE = 1;    //CN0/RA4: enable CN interrupt
    CNEN1bits.CN1IE = 1;    //CN1/RB4: enable CN interrupt
    CNEN2bits.CN30IE = 1;   //CN30/RA2: enable CN interrupt
    IPC4bits.CNIP = 0b111;  //set CN interrupt priority
    IFS1bits.CNIF = 0;      // clear CN interrupt flag
    IEC1bits.CNIE = 1;      //enable CN interrupt

}
void IOCheck(void)
{
    IEC1bits.CNIE = 0;  //turn off interrupts
    
    char sec[5];
    char min[5];
    char output[15];
    
    memset(sec,0,sizeof(sec));
    memset(min,0,sizeof(min));
    memset(output,0,sizeof(output));
    //This part waits for the button to be constantly pressed.
    while(PORTBbits.RB4 == 0 && PORTAbits.RA4 && PORTAbits.RA2){
        if(minute != 59){
            //This shows when the button is pressed
            //Disp2String("\rPB1 is pressed and minutes have been incremented");
            //Now we want to increment minute.
            minute++;
            sprintf(sec,"%d",second);
            sprintf(min,"%d",minute);
            strcpy(output,min);
            strcat(output,"m : ");
            strcat(output,sec);
            strcat(output,"s\0");
            Disp2String("\r"); 
            Disp2String(output);
            //Now we will show how minutes has been incremented.
            //Disp2Dec(minute);
        }
        //Will use this in order to create some time delay between the user 
        LATBbits.LATB8 = 1;
        Delay_ms(100);
        LATBbits.LATB8 = 0;
        Delay_ms(100);
    }
    //This part waits for the button to be constantly pressed
    while(PORTBbits.RB4 && PORTAbits.RA4 == 0 && PORTAbits.RA2){
        if(second != 59){
            //This shows when the button is pressed
            //Disp2String("\rPB2 is pressed and seconds have been incremented");
            //Now we want to increment seconds.
            second++;
            sprintf(sec,"%d",second);
            sprintf(min,"%d",minute);
            strcpy(output,min);
            strcat(output,"m : ");
            strcat(output,sec);
            strcat(output,"s\0");
            Disp2String("\r"); 
            Disp2String(output);
            //Now we will show how seconds has been incremented.
            //Disp2Dec(second);
        }
        LATBbits.LATB8 = 1;
        Delay_ms(100);
        LATBbits.LATB8 = 0;
        Delay_ms(100);
    }
    //This part needs to count down or pause based off of the short presses and possibly long presses.
    int check = 0;
    int count = 0;
    while(PORTBbits.RB4 && PORTAbits.RA4 && PORTAbits.RA2 == 0){
        if(count < 3){
            //Delay for a second
            Delay_ms(1000);
            count++;
            state = 1;
        }
        else{
            //reset
            state = 0;
            minute = 0;
            second = 0;
            Delay_ms(500);
        }
    }
    
    while(state==1){
        memset(sec,0,sizeof(sec));
        memset(min,0,sizeof(min));
        memset(output,0,sizeof(output));
        sprintf(sec,"%d",second);
        sprintf(min,"%d",minute);
        strcpy(output,min);
        strcat(output,"m : ");
        strcat(output,sec);
        strcat(output,"s\0");
        Disp2String("\r"); 
        Disp2String(output);
        Disp2String(" ");
        if(second==0&&minute==0){
            Disp2String("--ALARM");
            alarm = 1;
            if(PORTBbits.RB4 == 0 && PORTAbits.RA4 && PORTAbits.RA2){
                state = 0;
                alarm = 0;
                Disp2String("\r               ");
            }
            if(PORTBbits.RB4 && PORTAbits.RA4 == 0 && PORTAbits.RA2){
                state = 0;
                alarm = 0;
                Delay_ms(500);
                Disp2String("\r               ");
            }
        }
       
        if(second==0){
            if(minute>0){
                second=59;
                minute--;
            }
        }
        else{
            if(second>0){
                second--;
            }
        }
        
        if(alarm==0){
            if(light==0){
                LATBbits.LATB8 = 1;
                light = 1;
            }
            else{
                LATBbits.LATB8 = 0;
                light = 0;
            }
        }
        else{
          LATBbits.LATB8 = 1;  
        }
        
        Delay_ms(300);
        
        if(PORTBbits.RB4 && PORTAbits.RA4 && PORTAbits.RA2 == 0){
            state = 0;
            alarm = 0;
            Delay_ms(500);
        }
    }
    
    
    
    while(PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1 && PORTAbits.RA2 == 1){
        
        sprintf(sec,"%d",second);
        sprintf(min,"%d",minute);
        strcpy(output,min);
        strcat(output,"m : ");
        strcat(output,sec);
        strcat(output,"s\0");
        Disp2String("\r"); 
        Disp2String(output);
        LATBbits.LATB8 = 0;
    }
      
    return;
}