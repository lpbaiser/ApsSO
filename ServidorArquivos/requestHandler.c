#include "dynamicList.h"
#include <string.h>
#include <stdlib.h>
#include "requestHandler.h"
#include "request.h"
#include <semaphore.h>
#include <pthread.h>
#include "server.h"

#define BUFFER_SIZE 2048

void aguardaRequisicao(connection_t* connection){


    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    CONN_receive(connection, buffer, BUFFER_SIZE, 0);

    Request *request = (Request*) calloc(1, sizeof (Request));
    request = createRequest(connection, buffer);
    addRequestList(request);

    if (!strcmp(buffer, "sair")) {
        return;
    }


}

void* requestHandler(void* args) {

    connection_t* connection;
    connection = (connection_t*) args;

//    Request *stRequest = (Request*) malloc(sizeof (Request));
//    stRequest->connection = connection;
//    stRequest->path = "files/";
//    stRequest->typeRequest = 1;
//    addRequestList(stRequest);

    while (1) {
        aguardaRequisicao(connection);
    }

    CONN_close(connection);

}

void* addRequestList(Request* request) {
    pthread_mutex_lock(&mutexAddLista);
    addLastList(requestBuffer, request);
    pthread_mutex_unlock(&mutexAddLista);
    sem_post(&full);
}
