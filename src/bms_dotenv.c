#include "bms_dotenv.h"

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

// TODO(victor): Use hashmap
// TODO(victor): Create a hashmap...
//
typedef struct variable_t{
	char* key;
	char* value;
} variable_t;

static int bms_dotenv_variables_count = 0;
static variable_t bms_dotenv_variables[256] = {0};

int parse_dotenv(char* buffer) {
	char* buffer_copy = strdup(buffer);

	char** lines = calloc(256 , sizeof(char*));

	char *token;
	token = strtok(buffer_copy, "\n");

	int count = 0;
	// This part will retrive all lines from the buffer
	while(token != NULL) {
		while(isblank(*token) || isspace(*token))
			*token++;

		while(*token == '#') {
			token = strtok(NULL, "\n");
			if(token == NULL) {
				free(buffer_copy);
				free(lines);
				fprintf(stderr, "[ERROR] No lines found to parse\n");
				return -1;
			}
		} 
		
		lines[count++] = token;
		token = strtok(NULL,  "\n");
	}

	// This will process each line
	for(int i = 0; i < count; i++) {
		int parse_error = 0;
		char* key = strtok(lines[i], "=");
		char* value = strtok(NULL, "=");

		char* kptr = key;
		while(*kptr != 0) {
			if(isspace(*kptr)) {
				fprintf(stderr, "[WARN] Can't not parse line. File should have KEY=VALUE values.\n");
				parse_error = 1;
				break;
			}

			kptr++;
		}

		char* vptr = value;
		while(*vptr != 0) {
			if(isspace(*vptr)) {
				fprintf(stderr, "[WARN] Can't not parse line. File should have KEY=VALUE values.\n");
				parse_error = 1;
				break;
			}

			vptr++;
		}


		if(key == NULL || value == NULL) {
			fprintf(stderr, "[WARN] Can't not parse line. File should have KEY=VALUE values.\n");
			parse_error = 1;
		}

		if(parse_error) {
			continue;
		}
		
		variable_t var = {key, value};
		bms_dotenv_variables[bms_dotenv_variables_count++] = var;
	}

	free(lines);

	return 0;
}

int bms_dotenv_init(char* path) {
	char buffer[66536];

	if(path == NULL) {
		path = ".env";
	}

	int env_fd = open(path, O_RDONLY, 0);
	if(env_fd == -1) {
		perror("Failed to open/find .env file");
		return -1;
	}

	ssize_t nbytes;
	if((nbytes = read(env_fd, buffer, sizeof(buffer))) < 0) {
		perror("Failed to read from .env");
		return -1;
	}
	if(nbytes == 0) {
		fprintf(stderr, "[WARN] .env is currently empty");
		return -1;
	}

	if(parse_dotenv(buffer) < 0) {
		fprintf(stderr, "[ERROR] In function parse_dotenv(). Error while parsing file\n");
		return -1;
	}

	if(bms_dotenv_variables_count == 0) {
		fprintf(stderr, "[ERROR] Can't not parse any line\n");
		return -1;
	}

	return 0;
}


// TODO(victor): Use hashmap, for better search
// TODO(victor): Create a hashmap...

char* bms_dotenv_get(char* s) {
	for(int i = 0; i < bms_dotenv_variables_count; i++) {
		if(strcmp(bms_dotenv_variables[i].key, s) == 0) {
			return bms_dotenv_variables[i].value;
		}
	}

	return NULL;
}
