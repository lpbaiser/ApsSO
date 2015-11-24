#include "dynamicList.h"
#include <string.h>
#include <stdlib.h>
#include "requestHandler.h"
#include "request.h"
#include <semaphore.h>

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

void* addList(request req) {
    sem_wait(&mutexAddLista);
    addLastList(lista, req);
    sem_post(&mutexAddLista);
    sem_post(&mutexVazio);
}
