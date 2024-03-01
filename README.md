# C .env parser  

- Will find a .env file and will load the values from it. The values must me KEY=VALUE, without any space. And it will not remove quotes from VALUES.
- Support comment with #.
- It will probably only work in Unix systems.

## Build / Install

To build:
```
make build
```

To install:
```
sudo make
```
If you install it, you can link it with the flag -lbmsdotenv when compiling.

## Usage

.env
```
# API
API_KEY=1234567890abcdefghijklmnopqrstuvwxyz
API_URL=https://api.exemplo.com/v1
APP_NAME=Normar Tudo Normar
```

main.c
```c
#include <bms_dotenv.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	bms_dotenv_init(NULL);
	char* api_key = getenv("API_KEY");
	char* api_url = getenv("API_URL");
	char* app_name = getenv("APP_NAME");
	puts(api_key); 
	puts(api_url);
	puts(app_name);

	return EXIT_SUCCESS;
}
```
