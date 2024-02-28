#ifndef BMS_DOTENV_H
#define BMS_DOTENV_H

#include <stdio.h>

// TODO(victor): Use hashmap
// TODO(victor): Create a hashmap...
typedef struct variable_t{
	char* key;
	char* value;
} variable_t;

static int variables_count = 0;
static variable_t** variables = NULL;


//
// Will retrieve the values from the .env file
// return 0 for sucess and -1 for failure
//
// if path equals NULL, it will search in the current directory of the program
int bms_dotenv_init(char* path);

//
// Try to get value from .env based on the key
//
// Key is case sensitive, so you must type the exact value from .env file
// to get the correct value
//
// Will return NULL if can't get it.
//
char* bms_dotenv_get(char* key);

//
// Cleanup memory allocated from dotenv_init()
//
void bms_dotenv_finalize();

#endif // !BMS_DOTENV_H
