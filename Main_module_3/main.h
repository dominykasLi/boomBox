#ifndef MAIN_H
#define	MAIN_H

//Main game check if the player failed
void check_fail_state();

//Main game check if all of the modules are completed
void check_modules_left(int modules_left);

//Initialize the system
void init(void);

//Generation of the seed
void generate_random_seed(void);

//Sends all of the values to other modules using I2C
void send_gen_values(char series[], int health, int min, int sec);

//Checks if HP is reduced from modules or if the module is solved
void receive_slave_data(int *modules_left);




#endif	/* MAIN_H */