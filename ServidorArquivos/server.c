#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "connection.h"
#include "dynamicList.h"
#include <pthread.h>
#include <semaphore.h>
#include "workerThread.h"
#include "requestHandler.h"

#define BUFFER_SIZE 2048

List *requestBuffer;
pthread_mutex_t mutexAddLista;
sem_t full;
pthread_t *threads;

int dispatcher(int* listenSock, char* port) {

    connection_t* connection;


    //Aceitar conexões. Esta função retorna uma conexão (usando um novo socket) ou NULL.
    //listenSocket ainda pode ser chamado para aceitar outras conexões!
    connection = CONN_accept(*listenSock);

    //Verificar se houve sucesso ao conectar
    if (!connection) {
        fprintf(stderr, "Não foi possível conectar ao cliente remoto na porta %s!\n", port);
        return EXIT_FAILURE;
    }
    
    char* buffer = "Conectado com sucesso!";    
    CONN_send(connection, buffer, strlen(buffer), 0);
    
//    Request *stRequest = (Request*) malloc(sizeof(Request));
//    stRequest->connection = connection;
//    stRequest->path = "files/";
//    stRequest->typeRequest = 1;
//    addRequestList(stRequest);
    
    
    pthread_t* t;
    t = malloc(sizeof (pthread_t));
    pthread_create(t, NULL, requestHandler, (void*) connection);

    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    requestBuffer = createList();
    initializeList(requestBuffer);  
    
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutexAddLista, NULL);
    //Socket usado para aguardar a conexão
    int* listenSock;


    //Porta a ser usada pelo servidor... (use portas altas (10000+) para evitar conflitos com serviços já sendo executados)
    char* port;
    int nThreads = 1;

    //Verficar se a porta foi passada como argumento
    if (argc < 2) {
        fprintf(stderr, "uso: %s porta\n", argv[0]);
        return EXIT_FAILURE;
    }

    //porta é o primeiro argumento
    port = argv[1];
//    nThreads = atoi(argv[2]);

    int i;
    pthread_t* thread;
    for (i = 0; i < nThreads; i++) {
        thread = malloc(sizeof(pthread_t));
        pthread_create(thread, NULL, wakeThread, NULL);
    }

    listenSock = malloc(sizeof (int));
    *listenSock = 0;

    //Abrir socket para arguardar conexões
    *listenSock = CONN_listenTo((char*) port);

    while (!dispatcher(listenSock, port));

    //fechar o socket
    close(*listenSock);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutexAddLista);

    return EXIT_SUCCESS;

}

