#include "bms_dotenv.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFSIZE 4092 

int parse_line(char* token) {

	char* save_ptr = NULL;
	char* key = strtok_r(token , "=", &save_ptr);
	char* value = strtok_r(NULL, "\n", &save_ptr);

	if(key == NULL || value == NULL) {
		fprintf(stderr, "[WARN] Can't not parse line. File should have KEY=VALUE values.\n");
		return -1;
	}

	setenv(key, value, 0);
	return 0;
}

int parse_dotenv(char* buffer) {
	char* buffer_copy = strdup(buffer);


	char *token, *save_ptr = NULL;
	token = strtok_r(buffer_copy, "\n", &save_ptr);

	int count = 0;
	// get line
	while(token != NULL) {
		// skip any identation
		while(isblank(*token) || isspace(*token)) {
			token++;
		}

		if(*token == '#') {
			token = strtok_r(NULL, "\n", &save_ptr);
			continue;
		}
		
		//parsing line
		parse_line(token);
		
		//get line
		token = strtok_r(NULL, "\n", &save_ptr);
	}

	free(buffer_copy);

	return 0;
}

void bms_dotenv_init(char* path) {
	char buffer[BUFFSIZE] = {0};

	if(path == NULL) {
		path = ".env";
	}

	int env_fd = open(path, O_RDONLY, 0);
	if(env_fd == -1) {
		perror("Failed to open/find .env file");
		exit(EXIT_FAILURE);
	}

	ssize_t nbytes;
	if((nbytes = read(env_fd, buffer, BUFFSIZE)) < 0) {
		perror("Failed to read from .env");
		exit(EXIT_FAILURE);
	}

	if(nbytes == 0) {
		fprintf(stderr, "[WARN] .env is currently empty");
		return;
	}

	if(parse_dotenv(buffer) < 0) {
		fprintf(stderr, "[ERROR] In function parse_dotenv(). Error while parsing file\n");
		exit(EXIT_FAILURE);
	}

	return;
}
