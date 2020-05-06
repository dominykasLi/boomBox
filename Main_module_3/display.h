/**
  Display Driver API Header File

  @File Name
    display.h

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

#ifndef DISPLAY_H
#define	DISPLAY_H

/**
  Section: Included Files
*/

//#include <stdint.h>
//#include <stdbool.h>
//#include "main.h"

//Invoke, to display the number on the 7 segment, that is in the name of var.
int disp0[] = {0,0,1,1,1,1,1,1};
int disp1[] = {0,0,0,0,0,1,1,0};
int disp2[] = {0,1,0,1,1,0,1,1};
int disp3[] = {0,1,0,0,1,1,1,1};
int disp4[] = {0,1,1,0,0,1,1,0};
int disp5[] = {0,1,1,0,1,1,0,1};
int disp6[] = {0,1,1,1,1,1,0,1};
int disp7[] = {0,0,0,0,0,1,1,1};
int disp8[] = {0,1,1,1,1,1,1,1};
int disp9[] = {0,1,1,0,1,1,1,1};

/**
  Section: display APIs
*/

/**
  @Summary
    Gets time, displays numbers every second and reduces time by 1 second

  @Description
    First it gets minutes and seconds and seperates them by digit.
    Then if one second passes (130 overflows), start displaying digits.
    Finally reduces time by 1 second.

  @Preconditions
    TIMER0 has to be set up first

  @Param
    min - the current amount of minutes the display has calculated and/or
    showing.
    sec - the current amount of seconds the display has calculated and/or
    showing.
    health - the current amount of health the display has calculated and/or
    showing.

  @Returns
    None

  @Comment
    
*/
void display_loop(int *min, int *sec, int health);

/**
  @Summary
    Gets time, displays numbers every second and reduces time by 1 second.

  @Description
    First it gets minutes and seconds and seperates them by digit.
    Then if one second passes (130 overflows), start displaying digits.
    Finally reduces time by 1 second.

  @Preconditions
    Has to be called from display_loop function.

  @Param
    digit - the number to display ex.: 1 to display the number 1.
    data_pin - which of the seven segments to activate ex.: 2 to set display
    for the second seven segment.
    segment - if the segment needs to be on, set to 1, else to 0. 

  @Returns
    None

  @Comment
    
*/
void display(int digit, int data_pin, int segment);

/**
  @Summary
    Sets a random pattern to the 4 debug LEDs.

  @Description
    Sets the LEDs on or off randomly, using rand().

  @Preconditions
    None.

  @Param
    digit - the number to display ex.: 1 to display the number 1.
    data_pin - which of the seven segments to activate ex.: 2 to set display
    for the second seven segment.
    segment - if the segment needs to be on, set to 1, else to 0. 

  @Returns
    None.

  @Comment
    
*/
void led_series_set(char series[]);

/**
  @Summary
    Turns off 7 segment displays.

  @Description
    Sets the data by which to set the 7-segments to 0 and then updates the display.

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Comment
    
*/
void reset_segments(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    

#endif

#endif // DISPLAY_H

/**
 End of File
*/