/**
  @File Name
    display.c

  @Summary
    This is display system, to show numbers and LEDs on the main board

  @Description
    This source file provides APIs for displaying: lives, minutes, seconds and
    the 4 debug LEDs.
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
#include "display.h"
#include "main.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/pin_manager.h"

/**
  Section: Global Variables Definitions
*/

//Amount of times the Timer reset
int overFlowAmmountTMR0 = 0;
int overFlowAmmountTMR1 = 0;

//Amount of times until a second passes for Timer0
//Must match to sound secTMR0
int secTMR0 = 110;
/**
  Section: display APIs
*/

//Starts calculating the digits for the 7-segments
void display_loop(int *min, int *sec, int health) {
    int min1 = 0;   //First digit of the min var. etc...
    int min2 = 0;
    int sec1 = 0;
    int sec2 = 0;

    //Seperating the numbers to 1 digit each
    min1 = (*min) / 10;
    min2 = (*min) % 10;
    sec1 = (*sec) / 10;
    sec2 = (*sec) % 10;

    // check the overflow flag
    if(TMR0_HasOverflowOccured()){
        //Every 1ms increase the counter
        overFlowAmmountTMR0 += 1;
        
        // clear the TMR0 interrupt flag
        TMR0IF = 0;

        // Reload the TMR0 value
        TMR0_Reload();
        
        //secTMR0 is the closest amount to a second
        if(overFlowAmmountTMR0 >= secTMR0){
            overFlowAmmountTMR0 = 0;
            
            for(int i = 0; i < 8; i++) {
                //Second argument is the 7-segment place 
                //Ex.: 1 -> means minute first digit place
                display(min1, 1, i);
                display(min2, 2, i);
                display(sec1, 3, i);
                display(sec2, 4, i);
                display(health, 5, i);

                SHCLK = 1;
                SHCLK = 0;

                SER1 = 0;
                SER2 = 0;
                SER3 = 0;
                SER4 = 0;
                SER5 = 0;
            }
            STRCLK = 1;
            STRCLK = 0;
            
            //Reduces time by 1 second, and reduces minutes if sec reaches 0
            if((*sec) == 0 && (*min) > 0){
                (*min) -= 1;
                (*sec) = 60;
            }
            (*sec) -= 1;
        }
    }
}

//Sets the needed 7-segment's digit
void display(int digit, int data_pin, int segment){
   int state = 0;    //Whether to output_high or output_low
                     //If the 7-segment led segment is low it is set to 0
                     //If not set to 1, to output high on the Data pin
   
   //Chooses which number to display
   //Digit means what number to display in the current 7-segment
   if(digit == 0){
      state = disp0[segment];
   }else if(digit == 1){
      state = disp1[segment];
   }else if(digit == 2){
      state = disp2[segment];
   }else if(digit == 3){
      state = disp3[segment];
   }else if(digit == 4){
      state = disp4[segment];
   }else if(digit == 5){
      state = disp5[segment];
   }else if(digit == 6){
      state = disp6[segment];
   }else if(digit == 7){
      state = disp7[segment];
   }else if(digit == 8){
      state = disp8[segment];
   }else if(digit == 9){
      state = disp9[segment];
   }

   //If the digit is for the first seven segment, set Data pin to high, else low
   if(data_pin == 1 && state == 1){
      SER1 = 1;
   }else if(data_pin == 2 && state == 1){
      SER2 = 1;
   }else if(data_pin == 3 && state == 1){
      SER3 = 1;
   }else if(data_pin == 4 && state == 1){
      SER4 = 1;
   }else if(data_pin == 5 && state == 1){
      SER5 = 1;
   }
}

//Set debug LEDs randomly
void led_series_set(char series[]){
    //Set a random pattern to the LEDs
    for(int i = 0; i < 4; i++){
      series[i] = (rand() % 2);
    }
    //Set the LEDs to the pattern
    if(series[0] == 1){
        LED1 = 1;
    }
    if(series[1] == 1){
        LED2 = 1;
    }
    if(series[2] == 1){
        LED3 = 1;
    }
    if(series[3] == 1){
        LED4 = 1;
    }
    series[4] = 0;
    series[5] = 0;
    series[6] = 0;
    series[7] = 0;
    //series[0] = 1;
}

//Resets all of the 7-segments to zero
void reset_segments(void) {
   SER1 = 0;
   SER2 = 0;
   SER3 = 0;
   SER4 = 0;
   SER5 = 0;
   
   for(int i = 0; i < 8; i++) {
      SHCLK = 1;
      STRCLK = 1;
      SHCLK = 0;
      STRCLK = 0;
   }
}

/**
  End of File
*/
