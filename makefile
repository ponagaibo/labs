CC = g++
CFLAGS = -std=c++11

all: server client

server: thrServer.o
	$(CC) -o server thrServer.o -lpthread -L/usr/local/lib -lzmq $(CFLAGS)
client: thrClient.o
	$(CC) -o client thrClient.o -L/usr/local/lib -lzmq $(CFLAGS)

thrServer.o: thrServer.c
	$(CC) -c thrServer.c
thrClient.o: thrClient.c
	$(CC) -c thrClient.c
clean:
	rm -f *.o server client