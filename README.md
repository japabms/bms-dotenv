# C .env parser  

- Will find a .env file and will load the values from it. The values must me KEY=VALUE, without any space. And it will not remove quotes from VALUES.
- Support comment with #.
- It will probably only work in Unix systems.

I made it in like 3 hours, so it's not refined yet. But i think it is usable.

## Build / Install

To build:
```
make build
```

To install:
```
sudo make install
```
If you install it, you can link it with the flag -lbmsdotenv.

## Usage

.env
```
# API
API_KEY=1234567890abcdefghijklmnopqrstuvwxyz
API_URL=https://api.exemplo.com/v1
```

main.c
```c
#include <bms_dotenv.h>

int main(int argc, char *argv[])
{

	bms_dotenv_init(NULL);
	char* api_key = bms_dotenv_get("API_KEY");
	char* api_url = bms_dotenv_get("API_URL");

	bms_dotenv_finalize(); // will free api_key and api_url values.

	return EXIT_SUCCESS;
}
```
