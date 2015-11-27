#include "dynamicList.h"
#include <string.h>
#include <stdlib.h>
#include "requestHandler.h"
#include "request.h"
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 2048

void* aguardaRequisicao(connection_t connection) {
    uint8_t buffer[BUFFER_SIZE];
    while (1) {
        CONN_receive(connection, buffer, BUFFER_SIZE, 0);

        if (!strcmp(buffer, "sair")) {
            break;
        }
        request *req = (request*) calloc(1, sizeof (request));
        req = createRequest(connection, buffer);
        addList(req);
    }

}

void* addList(Request req) {
    pthread_mutex_lock(&mutexAddLista);
    addLastList(lista, req);
    pthread_mutex_unlock(&mutexAddLista);
    sem_post(&full);
}
