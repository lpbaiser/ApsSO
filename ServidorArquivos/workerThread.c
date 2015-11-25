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

void processLs(Request *r) {
    int p[2], backup;
    char buffer[BUFFER_SIZE];
    char buf[BUFFER_SIZE];

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

        CONN_send(r->connection, buffer, BUFFER_SIZE, 0);

        c = fgetc(f);
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
            removeFirstList(lista, &r);
            processLs(r);
        } else if (lista->first->data->typeRequest == 2) {
            removeFirstList(lista, r);
            processWget(lista->first->data);
        }
    }

    pthread_mutex_unlock(&mutexAddLista);

}

char* getNameArquivo(Request *r) {
    char nome[BUFFER_SIZE];
    while (strlen(r->path)) {

    }
}

char* inverteString(char *string) {
    int a,b;
    char auxiliar[strlen(string)];
    b = strlen(string) - 1; //strlen calcula a quantidade de caracteres que tem a string
    for (a = 0; string[a] != '\0'; a++) { //Repete enquanto nao chegar ao final da string
        auxiliar[b] = string[a];
        b--;
    }
    auxiliar[a] = '\0'; //Se nao colocar essa parte, o programa pode mostrar LIXO
    strcpy(string, auxiliar); //Copia para a variável string o conteúdo da variável auxiliar
}
