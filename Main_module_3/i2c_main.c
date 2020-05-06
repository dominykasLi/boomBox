#include <xc.h>
#include <pic18f24k22.h>
#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/pin_manager.h"

//Setup the I2C, needs clock value (100khz)
void I2C_Master_Init(const unsigned long c){
    SSPCON1 = 0b00101000;                   //Enables SDA and SCL and sets this as master
    SSPCON2 = 0;                            //Sets default values
    SSPADD = (_XTAL_FREQ/(4*c))-1;          //Sets baud rate 100khz
    SSPSTAT = 0;                            //Sets default values
    TRISC3 = 1;                             //Sets SCL to input
    TRISC4 = 1;                             //Sets SDA to input
    //Global interrupts enable
    GIE = 1;
    //Peripherals enable
    PEIE = 1;
    //Clear interrupt flag
    SSPIF = 0;
    //Synchronous serial port interrupt enable
    SSPIE = 1;
}
//Wait
void I2C_Master_Wait(void){
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

//Send start bit
void I2C_Master_Start(void){
    I2C_Master_Wait();
    SSPCON2bits.SEN = 1;
    while(SSPCON2bits.SEN == 1);
    PIR1bits.SSPIF = 0;
}

//Send repeat, used for read
void I2C_Master_RepeatedStart(void){
    I2C_Master_Wait();
    SSPCON2bits.RSEN = 1;
}

//Send stop bit
void I2C_Master_Stop(void){
    I2C_Master_Wait();
    SSPCON2bits.PEN = 1;            //Stop bit set
    while(SSPCON2bits.PEN);         //Wait for stop bit to be set
}

//Write to SSPBUF
void I2C_Master_Write(unsigned d){
    //I2C_Master_Wait();
    SSPBUF = d;                     //Write to register
    while(!SSPIF);                  //Wait for the ACK (9th clock cycle)
    PIR1bits.SSPIF = 0;             //Clear flag
    
    if(SSPCON2bits.ACKSTAT){        //ACK received (0 received, 1 NACK)
        SSPCON2bits.PEN = 1;        //Stop bit set
        while(SSPCON2bits.PEN);     //Wait for stop bit to be set
        return;
    }
}

//Write to SSPBUF address and data
void I2C_Master_Write_Address_Data(unsigned add, unsigned data){
    //I2C_Master_Wait();
    SSPBUF = add;                   //Write to register address
    while(!SSPIF);                  //Wait for the ACK (9th clock cycle)
    PIR1bits.SSPIF = 0;             //Clear flag
    
    if(SSPCON2bits.ACKSTAT){        //ACK received (0 received, 1 NACK)
        SSPCON2bits.PEN = 1;        //Stop bit set
        while(SSPCON2bits.PEN);     //Wait for stop bit to be set
        return;
    }
    
    SSPBUF = data;                  //Write to register address
    while(!SSPIF);                  //Wait for the ACK (9th clock cycle)
    PIR1bits.SSPIF = 0;             //Clear flag
    
    SSPCON2bits.PEN = 1;            //Stop bit set
    while(SSPCON2bits.PEN);         //Wait for stop bit to be set
}

//Read from SSPBUF and send ACK
unsigned short I2C_Master_Read(unsigned short a){
    unsigned short temp;
    I2C_Master_Wait();
    //Repeated start
    SSPCON2bits.RCEN = 1;
    while(!SSPIF);                  //Wait for the ACK (9th clock cycle)
    PIR1bits.SSPIF = 0;             //Clear flag
    I2C_Master_Wait();
    //Read value
    temp = SSPBUF;
    I2C_Master_Wait();
    //If everything is okay, send Acknowledge
    SSPCON2bits.ACKDT = (a)?0:1;            //NACK to finish receiving
    SSPCON2bits.ACKEN = 1;                  //Start sending NACK
    I2C_Master_Stop();
    return temp;
}

//Read from SSPBUF and send ACK
unsigned short I2C_Master_Read_With_Address(unsigned short add){
    int temp_data = 0;
    
    I2C_Master_Start();             
    while(SSPCON2bits.SEN);
    PIR1bits.SSPIF = 0;
    
    
    I2C_Master_Write(add);
    
    SSPSTATbits.BF = 0;
    
    SSPCON2bits.RCEN = 1;
    while(SSPCON2bits.RCEN);
    PIR1bits.SSPIF = 0;
    
    temp_data = SSPBUF;
    
    /*SSPCON2bits.ACKDT = 0;          //NACK to finish receiving
    SSPCON2bits.ACKEN = 1;          //Start sending NACK
    while(SSPCON2bits.ACKEN);*/
    
    
    
    SSPCON2bits.ACKDT = 1;          //NACK to finish receiving
    SSPCON2bits.ACKEN = 1;          //Start sending NACK
    while(SSPCON2bits.ACKEN);
    
    SSPCON1bits.SSPOV = 0;
    SSPCON2bits.ACKEN = 0;          //Start sending NACK
    SSPCON2bits.ACKDT = 0;          //NACK to finish receiving
    
    I2C_Master_Stop();
    while(!SSPSTATbits.P);
    PIR1bits.SSPIF = 0;
    /*LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;*/
    return temp_data;
}