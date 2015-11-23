/* 
 * File:   WorkerThread.c
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 20, 2015, 10:40 AM
 */

#include "requestHandler.h"
#include "connection.h"
#include "dynamicList.h"
#include <pthread.h>

#define nThread int 4



void processLs(char *path){
    system(path);
}

void processWget(char *path){
    
}

//void createThreads(int numThreads) {
//
//    *vetorThreads = (vetorThreads) calloc(numThreads, sizeof (vetorThreads));
//
//    int i;
//    for (i = 0; i < numThreads; i++) {
//        Thread = (Thread) malloc(sizeof (Thread));
//        pthread_t* t;
//        t = malloc(sizeof (pthread_t));
//        Thread->thread = t;
//        Thread->isWorking = 0;
//        vetorThreads[i] = Thread;
//    }
//
//    printf(" %d", vetorThreads->threads[i]->isWorking);
//
//}

//void wakeThread(List* requestBuffer) {
//    requestBuffer->first;
//
//    while (1) {
//        if (requestBuffer->size > 0) {
//            if ()
//            }
//    }
//

//}