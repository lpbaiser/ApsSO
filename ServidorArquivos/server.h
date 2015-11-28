/* 
 * File:   server.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 24, 2015, 8:27 PM
 */

#pragma once





#include <pthread.h>
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


extern List *requestBuffer;
extern pthread_mutex_t mutexAddLista;
extern sem_t full;
extern pthread_t *threads;

int main(int argc, char** argv);


int dispatcher(int* listenSock, char* port);





