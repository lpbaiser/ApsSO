#include "dynamicList.h"
#include <string.h>
#include <stdlib.h>
#include "requestHandler.h"
#include "request.h"
#include <semaphore.h>
#include <pthread.h>
#include "server.h"

#define BUFFER_SIZE 2048

void* aguardaRequisicao(void* args) {
    
    connection_t* connection;
    connection = (connection_t*) args;
    
    
    char buffer[BUFFER_SIZE];
    while (1) {
        CONN_receive(connection, buffer, BUFFER_SIZE, 0);

        if (!strcmp(buffer, "sair")) {
            break;
        }
        Request *request = (Request*) calloc(1, sizeof (Request));
        request = createRequest(connection, buffer);
        addList(request);
    }
    CONN_close(connection);

}

void* addList(Request* request) {
    pthread_mutex_lock(&mutexAddLista);
    addLastList(requestBuffer, request);
    pthread_mutex_unlock(&mutexAddLista);
    sem_post(&full);
}
