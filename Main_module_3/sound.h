/**
  Sound API Header File

  @File Name
    sound.h

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

#ifndef SOUND_H
#define	SOUND_H

/**
  Section: Included Files
*/

/**
  Section: sound APIs
*/

/**
  @Summary
    Generates a beep sound

  @Description
    Generates a beep sound every second and also when a long beep, when time 
    runs out.

  @Preconditions
    TIMER0 has to be set up first

  @Param
    min - current minutes
    sec - current seconds    

  @Returns
    None

  @Comment
    
*/
void beep_sound(int min, int sec);

/**
  @Summary
    Makes the system stop beeping

  @Description
    Turns off the Buzzer

  @Preconditions

  @Param
    
  @Returns
    None

  @Comment
    
*/
void reset_beep_sound(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    

#endif

#endif	/* SOUND_H */

/**
 End of File
*/