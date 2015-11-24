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


#define BUFFER_SIZE 2048

void processLs(request *r) {
    int p[2], backup;
    char buffer[2048];
    char buf[2048];

    backup = dup(1);
    close(0);
    close(1);

    pipe(p);
    char path = "ls";
    strcat(path, r->path);
    system(path);
    dup2(backup, 1);

    while (fgets(buf, 1000, stdin)) {
        strcat(buffer, buf);
    }

    CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
}

void processWget(request *r) {

    FILE *f;
    char c;
    char buffer[BUFFER_SIZE];
    f = fopen(r->path, "r");

    if (f == NULL) {
        perror("Error opening file");
        //        return -1;
    } else {
        c = getc(f);
        while (c != EOF) {
            strcat(buffer, c);
            if (strlen(buffer) == 2048) {
                CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
                memset(buffer, (char) 0, sizeof (char)*BUFFER_SIZE);
            }
        }
        if (strlen(buffer) >= 1) {
            CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
        }

        memset(buffer, (char) 0, sizeof (char)*BUFFER_SIZE);
        buffer = "EOF";
        CONN_send(r->connection, buffer, BUFFER_SIZE, 0);
    }
}

/*
 * ver se tem item na lista
 * wait no semaforo
 * travar a lista
 * retira da lista
 * destrava lista
 */
void wakeThread() {

    sem_wait(&full);
    pthread_mutex_lock(&mutexAddLista);
    
    if (lista->size > 0) {
        request *r = (request) malloc(sizeof (request));
        if (lista->first->data->typeRequest == 1) {
            removeFirstList(lista, r);
            processLs(r);
        } else if (lista->first->data->typeRequest == 2) {
            removeFirstList(lista, r);
            processWget(lista->first->data);
        }
    }
    
    pthread_mutex_unlock(&mutexAddLista);

}

