#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <bms_dotenv.h>

int main(int argc, char *argv[])
{

	if(bms_dotenv_init(NULL) < 0) {
		return -1;
	}

	char* api_key = bms_dotenv_get("API_KEY");
	if(api_key == NULL) {
		// cannot retrieve the value
	}
	char* api_url = bms_dotenv_get("API_URL");
	if(api_url == NULL) {
		// cannot retrieve the value
	}
	


	char* host = bms_dotenv_get("HOST");
	if(host == NULL) {
		// cannot retrieve the value
	}
	char* port = bms_dotenv_get("PORT");
	if(port == NULL) {
		// cannot retrieve the value
	}

	bms_dotenv_finalize();

	return EXIT_SUCCESS;
}
