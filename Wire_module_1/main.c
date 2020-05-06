/**
  Main Source File

  File Name:
    main.c

  Summary:
    This is the main file

  Description:
    This header file provides implementations for driver APIs for all modules
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC18F14K22
        Driver Version    :  2.00
*/

#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "i2c_slave.h"

int hp = 0;                                     //The main modules generated HP
int min = 0;                                    //The main modules generated minutes
int sec = 0;                                    //The main modules generated seconds
char series[8] = {0, 0, 0, 0, 0, 0, 0, 0};      //The main modules generated led sequence
                                                //Must be set to 0

/*
                         Main application
 */

void main(void){
    // Initialize the device
    SYSTEM_Initialize();

    I2C_Slave_Init(0x50);
    
    get_series(series);
    
    int correct_wires_left = 2;            //How many wires left to cut
    
    
    
    while(1){
        data_to_send(3);
    }
}



/**
 End of File
*/