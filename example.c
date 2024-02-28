#include "bms_dotenv.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{


	if(bms_dotenv_init(NULL) < 0) {
		return -1;
	}

	char* api_key = bms_dotenv_get("API_KEY");
	if(api_key == NULL) {
		// do something
	}
	char* api_url = bms_dotenv_get("API_URL");
	if(api_url == NULL) {
		// do something
	}
	

	puts(api_key);
	puts(api_url);

	char* host = bms_dotenv_get("HOST");
	if(host == NULL) {
		// do something
	}
	char* port = bms_dotenv_get("PORT");
	if(port == NULL) {
		// do something
	}

	puts(host);
	puts(port);


	bms_dotenv_finalize();

	return EXIT_SUCCESS;
}
