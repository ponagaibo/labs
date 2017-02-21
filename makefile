CC = gcc
CFLAGS = -std=gnu99 

all: bank client

bank: vect.o bank.o
	gcc -o bank vect.o bank.o -L/usr/local/lib -lzmq
client: client.o
	gcc -o client client.o -L/usr/local/lib -lzmq

vect.o: vect.c
	gcc -c vect.c
bank.o: bank.c
	gcc -c bank.c
client.o: client.c
	gcc -c client.c
clean:
	rm -f *.o bank client
