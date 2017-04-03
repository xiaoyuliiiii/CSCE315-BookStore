
CC=g++
STD=-std=c++11
CFLAGS=

all: main.o books_data.o courses_data.o
	$(CC) $(STD) -o book main.o books_data.o courses_data.o
	
main.o: main.cpp
	$(CC) $(STD) -c main.cpp
	
books_data.o: books_data.cpp books_data.h
	$(CC) $(STD) -c books_data.cpp books_data.h

courses_data.o: courses_data.cpp courses_data.h
	$(CC) $(STD) -c courses_data.cpp courses_data.h

clean:
	rm -rf *o book *.gch
