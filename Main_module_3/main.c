#include "mcc_generated_files/mcc.h"
#include "display.h"
#include "sound.h"
#include "main.h"
#include "i2c_main.h"

//The ammount of tries the player has
int health = 2;

//Starting minutes and seconds
int min = 54;
int sec = 32;

//The first 4 control the 4 LEDs (On or Off)
char series[] = {0,0,0,0,0,0,0,0};

//Initialize the system
void init(void){
    //Initialize the device
    SYSTEM_Initialize();
    
    //Initialize I2C
    I2C_Master_Init(100000);
    
    //Generation of the seed
    generate_random_seed();
    
    //Reset displays
    reset_segments();
    
    //Start TMR0
    TMR0_StartTimer();
    
    //Turn on or off randomly 4 leds and get the values
    led_series_set(series);
}

//Using EEPROM to set a random seed
void generate_random_seed(void){   
    srand(DATAEE_ReadByte(0x0));
    DATAEE_WriteByte(0x0, DATAEE_ReadByte(0x0) + 0x1);
}

//Check if the game is over
void check_fail_state(void){ 
    if((min <= 0 && sec < 0) || (health <= 0)){
        //2 seconds for the player to understand he lost
        __delay_ms(2000);
        //Reset the sound, so no beeping is heard
        reset_beep_sound();
        //Reset the display, turn everything off
        reset_segments();
        //Infinite loop, so that the game would not restart
        while(1);
    }
}

//Main game check if all of the modules are completed
void check_modules_left(int modules_left){
    if(modules_left <= 0){
        while(1);
    }
}

//Sends all of the values to other modules using I2C
void send_gen_values(char series[], int health, int min, int sec){   
    int bin;
    int i;
    int sync = 99;                  //Synchronisation value, so slaves would know that we are sending a series of data
    
    for (bin = 0, i = 0; i < 8; ++i ){
       bin = bin << 1;
       bin = bin + series[i];
    }
    
    //Synchronization value (to start counting states for the slave)
    I2C_Master_Start();
    I2C_Master_Write_Address_Data(SLAVE1_WRT_ADDR, sync);
    I2C_Master_Stop();
    
    //Send HP
    I2C_Master_Start();
    I2C_Master_Write_Address_Data(SLAVE1_WRT_ADDR, health);
    I2C_Master_Stop();
    
    //Send Minutes
    I2C_Master_Start();
    I2C_Master_Write_Address_Data(SLAVE1_WRT_ADDR, min);
    I2C_Master_Stop();
    
    //Send Seconds
    I2C_Master_Start();
    I2C_Master_Write_Address_Data(SLAVE1_WRT_ADDR, sec);
    I2C_Master_Stop();
    
    //Send LEDs
    I2C_Master_Start();
    I2C_Master_Write_Address_Data(SLAVE1_WRT_ADDR, bin);
    I2C_Master_Stop();
}

void receive_slave_data(int *modules_left){
    int temp = -1;
    
    temp = I2C_Master_Read_With_Address(SLAVE1_READ_ADDR);
    //0 means default value, do nothing
    //1 means reduce hp
    //2 means module solved
    
    if(temp == 3){                //Checks if data is correct
            LED1 = 1;
            LED2 = 1;
            LED3 = 1;
            LED4 = 1;
            __delay_ms(3000);
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
            LED4 = 0;
            __delay_ms(3000);
        }
    //I2C_Master_Stop();
}

//Main function
int main(int argc, char** argv){
    //Initialize the system
    init();

    //How many modules left to solve
    int modules_left = 2; 
    
    //Wait and send data to all modules
    __delay_ms(20);
    //send_gen_values(series, health, min, sec);
    //receive_slave_data(&modules_left);
    __delay_ms(20);
    //send_gen_values(series, health, min, sec);
    __delay_ms(20);
    //receive_slave_data(&modules_left);
    
    reset_segments();
    __delay_ms(200);

    while (1) {        
        //Displays and counts the numbers
        display_loop(&min, &sec, health);
        
        //Send data to modules (time, hp...)
        //send_gen_values(series, health, min, sec+1);
        
        //Beeping sound generation
        beep_sound(min, sec);
        
        //Checks if HP is reduced from modules or if the module is solved
        receive_slave_data(&modules_left);
        
        

        //Check if all modules are solved
        //check_modules_left(modules_left);

        //Checks time and health
        //check_fail_state();
         
    }  
    return (EXIT_SUCCESS);
}

/**
 End of File
*/
