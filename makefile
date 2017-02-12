TARGET = lab5
CC=g++
FLAGS = -std=c++11 
default: 
	g++ *.cpp -o lab5 $(FLAGS)
clean:
	rm -rf da2 *gcov *gcno *gcda
