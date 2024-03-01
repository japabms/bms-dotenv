#ifndef BMS_DOTENV_H
#define BMS_DOTENV_H

#include <stdio.h>


/*
 * Will retrieve the values from the .env file
 * if path equals NULL, it will search in the current directory of the program
*/
void bms_dotenv_init(char* path);


#endif // !BMS_DOTENV_H
