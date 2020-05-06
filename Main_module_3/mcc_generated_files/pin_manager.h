/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC18F24K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

//First module address for I2C
#define SLAVE1_WRT_ADDR   0x50 
#define SLAVE1_READ_ADDR  0x51 

//Second modules address for I2C
#define SLAVE2_WRT_ADDR   0x4 
#define SLAVE2_READ_ADDR  0x5 

//Declaring ports
#define SHCLK   LATBbits.LATB2     //74HC595 Shift clock
#define STRCLK  LATBbits.LATB1     //74HC595 Store clock
#define SER4    LATBbits.LATB0     //74HC595 Data pin of segment 1
#define SER3    LATBbits.LATB3     //74HC595 Data pin of segment 2
#define SER2    LATBbits.LATB4     //74HC595 Data pin of segment 3
#define SER1    LATBbits.LATB5     //74HC595 Data pin of segment 4
#define SER5    LATCbits.LATC5     //74HC595 Data pin of segment 5
#define SND1    LATAbits.LATA0     //Buzzer contact 1
#define SND2    LATAbits.LATA1     //Buzzer contact 2
#define LED1    LATAbits.LATA2     //Debug led, one of 4 yellow
#define LED2    LATAbits.LATA3     //Debug led, one of 4 green
#define LED3    LATAbits.LATA4     //Debug led, one of 4 blue
#define LED4    LATAbits.LATA5     //Debug led, one of 4 

//Declaring tris
#define SHCLK_TRIS   TRISBbits.TRISB2     //74HC595 Shift clock
#define STRCLK_TRIS  TRISBbits.TRISB1     //74HC595 Store clock
#define SER4_TRIS    TRISBbits.TRISB0     //74HC595 Data pin of segment 1
#define SER3_TRIS    TRISBbits.TRISB3     //74HC595 Data pin of segment 2
#define SER2_TRIS    TRISBbits.TRISB4     //74HC595 Data pin of segment 3
#define SER1_TRIS    TRISBbits.TRISB5     //74HC595 Data pin of segment 4
#define SER5_TRIS    TRISCbits.TRISC5     //74HC595 Data pin of segment 5
#define SND1_TRIS    TRISAbits.TRISA0     //Buzzer contact 1
#define SND2_TRIS    TRISAbits.TRISA1     //Buzzer contact 2
#define LED1_TRIS    TRISAbits.TRISA2     //Debug led, one of 4 yellow
#define LED2_TRIS    TRISAbits.TRISA3     //Debug led, one of 4 green
#define LED3_TRIS    TRISAbits.TRISA4     //Debug led, one of 4 blue
#define LED4_TRIS    TRISAbits.TRISA5     //Debug led, one of 4 


/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/