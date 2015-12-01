/* 
 * File:   WorkerThread.c
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 20, 2015, 10:40 AM
 */

#include "requestHandler.h"
#include "connection.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "workerThread.h"
#include "dynamicList.h"
#include "server.h"
#include "request.h"


#define BUFFER_SIZE 2048

/*
 * ver se tem item na lista
 * wait no semaforo
 * travar a lista
 * retira da lista
 * destrava lista
 */
void* wakeThread() {

    sem_wait(&full);
    pthread_mutex_lock(&mutexAddLista);
    Request *r = (Request*) calloc(1, sizeof (Request));

    if (requestBuffer->size > 0) {
        if (requestBuffer->first->data->typeRequest == 1) {
            r = requestBuffer->first->data;
            removeFirstList(requestBuffer, r);
            processLs(r);
        } else if (requestBuffer->first->data->typeRequest == 2) {
            removeFirstList(requestBuffer, r);
            processWget(requestBuffer->first->data);
        }
    }

    pthread_mutex_unlock(&mutexAddLista);

}

void processLs(Request *r) {
    int p[2], backup;
    char buffer[BUFFER_SIZE];
    char buf[BUFFER_SIZE];

    backup = dup(1);
    close(0);
    close(1);

    pipe(p);
    char* path = malloc(sizeof (char));
    strcpy(path, "ls ");
    strcat(path, r->path);
    system(path);
    dup2(backup, 1);

    while (fgets(buf, 1000, stdin)) {
        strcat(buffer, buf);
    }

//    if (buf == NULL) {
//        char *typeRequest = "erro";
//        strcpy(buffer, "Diretório/Arquivo não encontrado");
//        CONN_send(r->connection, typeRequest, strlen(typeRequest), 0);
//        CONN_send(r->connection, buffer, strlen(typeRequest), 0);
//    } else {

        char typeRequest[2] = "ls";
        CONN_send(r->connection, typeRequest, 2, 0);

        CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
    
}

void processWget(Request *r) {

    FILE *f;
    char c;
    char buffer[BUFFER_SIZE];
    f = fopen(r->path, "r");

    if (f == NULL) {
        perror("Error opening file");
        //        return -1;
    } else {

        memset(buffer, (char) 0, sizeof (char)*BUFFER_SIZE);
        CONN_send(r->connection, getNameArquivo(r), BUFFER_SIZE, 0);
        memset(buffer, (char) 0, sizeof (char)*BUFFER_SIZE);

        c = fgetc(f);
        while (c != EOF) {
            strcat(buffer, &c);
            if (strlen(buffer) == 2048) {
                CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
                memset(buffer, (char) 0, sizeof (char)*BUFFER_SIZE);
            }
        }
        if (strlen(buffer) >= 1) {
            CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
        }

        memset(buffer, (char) 0, sizeof (char)*BUFFER_SIZE);

        strcpy(buffer, "EOF");
        //        buffer = "EOF";

        CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
    }
}

char* getNameArquivo(Request* r) {
    char *nome;
    nome = r->path;
    int i;
    for (i = strlen(r->path) - 1; i > 0; i--) {
        if (nome[i] != '/') {
            break;
        }
    }
    for (; i < strlen(r->path); i++) {
        nome[i] = r->path[i];
    }
    return nome;
}


