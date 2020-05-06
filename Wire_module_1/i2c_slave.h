#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

/**
   @Param
    Address value for slave
   @Returns
    None
   @Description
    Sets this slaves address
   @Example
    I2C_Slave_Init(0x50);
 */
void I2C_Slave_Init(short address);

/**
   @Param
    None
   @Returns
    Value of data received from master
   @Description
    Gets the data received
   @Example
    data_received_from_master = get_data();
 */
int get_data(void);

/**
   @Param
    Data to send
   @Returns
    none
   @Description
    Sets data to send
   @Example
    data_to_send(0x05);
   @Comments
    0 means default value, do nothing
    1 means reduce hp
    2 means module solved
 */
void data_to_send(int data);

/**
   @Param
    The received value from master
   @Returns
    None
   @Description
    Sets received HP, min, sec and series to internal variables
   @Example
    state_machine(0x07);
 */
void state_machine(int value);

/**
   @Param
    Value that was received from master
   @Returns
    None
   @Description
    Decodes the value for the LED series (ex.: 170 > 0b00001111)
   @Example
    get_led_status(0x07);
   @Comment
    //series[7] is yellow
    //series[6] is green
    //series[5] is blue2
    //series[4] is blue1
 */
void get_led_status(int incoming);

/**
   @Param
    Series value to get from master
   @Returns
    None
   @Description
    Gets the masters LEDs values
   @Example
    get_series(series);
 */
void get_series(char leds[]);

#endif	/* I2C_SLAVE_H */

