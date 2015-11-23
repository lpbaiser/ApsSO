CC=gcc
LDFLAGS=-lpthread
CFLAGS=-O0 -ggdb

all: 
	$(CC) -c connection.c $(CFLAGS)
	$(CC) -c dynamicList.c $(CFLAGS)
	$(CC) -c request.c $(CFLAGS)
	$(CC) -o client client.c connection.o $(LDFLAGS)
	$(CC) -o server server.c connection.o dynamicList.o $(LDFLAGS)
	$(CC) -c requestHandler.c $(CFLAGS)
	$(CC) -o workerThread workerThread.c workerThread.o $(LDFLAGS)
