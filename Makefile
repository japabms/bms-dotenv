CC = gcc
FLAGS = -Wall -Wextra
SRC = src/*.c

OBJ = bmsdotenv.o
LIB = libbmsdotenv.so

default: build install

build: 
	$(CC) $(CFLAGS) -c -fpic -o $(OBJ) $(SRC)
	$(CC) -shared -fpic -o $(LIB) $(OBJ)
	rm $(OBJ)


install:
	sudo mv $(LIB) /usr/lib
	sudo cp src/bms_dotenv.h /usr/include

