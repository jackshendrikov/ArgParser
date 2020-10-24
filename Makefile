CC=g++

all: main

main: ArgParser.o main.o
	$(CC) ArgParser.o main.o -o main

ArgParser.o: ArgParser.cpp
	$(CC) -c ArgParser.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -rf *.o main