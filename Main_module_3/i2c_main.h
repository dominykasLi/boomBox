#ifndef I2C_MAIN_H
#define	I2C_MAIN_H

/**
   @Param
    Speed value ex. 100000 (100khz)
   @Returns
    none
   @Description
    I2C initialization
   @Example
    I2C_Master_Init(100000);
 */
void I2C_Master_Init(const unsigned long c);

/**
   @Param
    A acknowledge 0, always 0
   @Returns
    Data read
   @Description
    Reads from SSPBUF from slave
   @Example
    temp = I2C_Master_Read(0);
 */
unsigned short I2C_Master_Read(unsigned short a);

/**
   @Param
    none
   @Returns
    none
   @Description
    Waits on the bus for transmission
   @Example
    I2C_Master_Wait();
 */
void I2C_Master_Wait(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sends start bit
   @Example
    I2C_Master_Start();
 */
void I2C_Master_Start(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sends repeated start bit
   @Example
    I2C_Master_RepeatedStart();
 */
void I2C_Master_RepeatedStart(void);

/**
   @Param
    none
   @Returns
    none
   @Description
    Sends stop bit
   @Example
    I2C_Master_Stop();
 */
void I2C_Master_Stop(void);

/**
   @Param
    Data to be written
   @Returns
    none
   @Description
    Sends data to I2C bus (slave), also used to send address of slave
   @Example
    I2C_Master_Write(0x02);
 */
void I2C_Master_Write(unsigned d);

/**
   @Param
    Address and data to be sent
   @Returns
    none
   @Description
    Sends data to I2C bus (slave), also used to send address of slave
   @Example
    I2C_Master_Write(0x02, 0x05);
 */
void I2C_Master_Write_Address_Data(unsigned add, unsigned data);

/**
   @Param
    Address to send to
   @Returns
    Data read
   @Description
    Reads from SSPBUF from slave
   @Example
    temp = I2C_Master_Read(0x03);
 */
unsigned short I2C_Master_Read_With_Address(unsigned short add);

#endif	/* I2C_MAIN_H */

