#include <xc.h>
#include <pic18f14k22.h>
#include "main.h"


short z;                    //Temp value to store SSPBUF value
int received;               //Data that is received from master
int value_to_send = 0;      //Data to send to master
int sent_state = 0;
char series[8];

//Gets the main module LED status and sends it to series variable
void get_led_status(int incoming){
    int c, k;
    int bin = incoming;
    for (c = 0; c < 8; ++c){
         k = bin >> c;
         if (k & 1){
            series[c] = 1;
         }else{
            series[c] = 0;
         }
    } 
}

void get_series(char leds[]){
    leds[7] = series[7];
    leds[6] = series[6];
    leds[5] = series[5];
    leds[4] = series[4];
}

void state_machine(int value){
    //Start 
    if(value == 99){
        sent_state = -2;
    }
    sent_state += 1;
    
    //Set HP value
    if(sent_state == 0){
        hp = value;
    }
    //Set minutes value
    if(sent_state == 1){
        min = value;
    }
    //Set seconds value
    if(sent_state == 2){
        sec = value;
    }
    //Set series value
    if(sent_state == 3){
        get_led_status(value);
    }
}

void __interrupt() I2C_Slave_Read(){ 
    //Interrupt is generated by HW
    if(SSPIF == 1){
        //Start clock stretching, not letting master to do anything
        SSPCON1bits.CKP = 0;
        
        //If a collision happened or overflow
        if ((SSPCON1bits.SSPOV) || (SSPCON1bits.WCOL)){
            z = SSPBUF;                 //Read the previous value to clear the buffer
            SSPCON1bits.SSPOV = 0;      //Clear the overflow flag
            SSPCON1bits.WCOL = 0;       //Clear the collision bit
            SSPCON1bits.CKP = 1;        //Let the master continue
        }
        
        //If Master is sending data to slave
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW){
            z = SSPBUF;                 //Got address
            SSPCON1bits.CKP = 1;        //Lets master do its thing
            while(!SSPSTATbits.BF);     //Wait for clear SSPBUF
            received = SSPBUF;          //Receive value from master
            
            state_machine(received);
            
            SSPCON1bits.CKP = 1;        //Let master continue
            
            //If Master is reading data from slave
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;                 //Read address
            SSPSTATbits.BF = 0;
            while(SSPSTATbits.BF);     //Wait for clear SSPBUF
            
            SSPBUF = 3;     //Set data to send
            //value_to_send = 0;          //Default value, means nothing to do
            SSPCON1bits.CKP = 1;        //Let master continue
            LATCbits.LATC2 = 1;         //Debug LED
        }
        
        //Reset interrupt, so it could happen again
        SSPIF = 0;
    }
}

//Set data value to be sent
void data_to_send(int data){
    value_to_send = data;
}

void I2C_Slave_Init(short address){
    //Set speed 100khz or 400khz (looks like its set to 400khz?)
    SSPSTAT = 0x80;
    //Set slave address
    SSPADD = address;
    //I2C slave mode, 7 bit address
    SSPCON1 = 0x36;
    //Clock stretching is enabled
    SSPCON2 = 0x01;
    //Global interrupts enable
    GIE = 1;
    //Peripherals enable
    PEIE = 1;
    //Clear interrupt flag
    SSPIF = 0;
    //Synchronous serial port interrupt enable
    SSPIE = 1;
    //Dont forget to set SDA and SCL to input!
}
