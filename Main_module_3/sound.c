/**
  @File Name
    sound.c

  @Summary
    All things related to sound is set here.

  @Description
    This file generates the beeping sound every second and the win/lose sound.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F24K22
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10
*/

/**
  Section: Included Files
*/

#include <xc.h>
//#include "main.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/pin_manager.h"

/**
  Section: Global Variables Definitions
*/

//Amount of times the Timer reset
int overFlowAmmountTMR0 = 0;
int overFlowAmmountTMR1 = 0;

//Amount of times until a second passes for Timer0
//Must match to display secTMR0
int secTMR0 = 110;

/**
  Section: sound APIs
*/

//Beep every second
void beep_sound(int min, int sec){
    //Strange effect that seconds should be set to 0, in order for the beep to
    //activate when the timer shows 1 second.
    if(min > 0 || sec >= 0){
        if(overFlowAmmountTMR0 == 0){
            // clear the TMR0 interrupt flag
            TMR0IF = 0;
        
            // Reload the TMR1 value
            TMR0_Reload();
            
            //Turn on Buzzer
            SND1 = 1;
        }
        //10 is just a beep length that sounds nice
        if(overFlowAmmountTMR0 >= (secTMR0 / 10)){
            SND1 = 0;
        }
    }
    //Strange effect that seconds should be set to -1, in order for the beep to
    //activate when the timer shows 0 seconds.
    if(min == 0 && sec == -1){
        if(overFlowAmmountTMR0 == 0){
            // clear the TMR0 interrupt flag
            TMR0IF = 0;
        
            // Reload the TMR1 value
            TMR0_Reload();
            
            //Turn on Buzzer
            SND1 = 1;
        }
        // is just a beep length that sounds nice
        if(overFlowAmmountTMR0 == secTMR0){
            SND1 = 0;
        }
    }
}

//Stop beeping
void reset_beep_sound(void){
    SND1 = 0;
    SND2 = 0;
}

/**
  End of File
*/