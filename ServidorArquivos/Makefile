#CC=gcc
#LDFLAGS=-lpthread
#CFLAGS=-O0 -ggdb

all: 
	
	gcc -c connection.c server.c dynamicList.c requestHandler.c request.c workerThread.c -ggdb -Wall
	gcc -o server server.o connection.o dynamicList.o requestHandler.o request.o workerThread.o -lpthread -ggdb
	gcc -c client.c connection.c -ggdb
	gcc -o client client.o connection.o -lpthread -ggdb
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf client server
	  
	#$(CC) -c connection.c $(CFLAGS)#
	#$(CC) -c dynamicList.c $(CFLAGS)#
	#$(CC) -c request.c $(CFLAGS)#
	#$(CC) -c requestHandler.c dynamicList.o $(CFLAGS)#
	#$(CC) -o client client.c connection.o $(LDFLAGS)#
	
	#$(CC) -o server server.c connection.o dynamicList.o $(LDFLAGS)#
	#$(CC) -o requestHandler requestHandler.c dynamicList.o $(LDFLAGS)#
	#$(CC) -o workerThread workerThread.c workerThread.o $(CFLAGS)#
