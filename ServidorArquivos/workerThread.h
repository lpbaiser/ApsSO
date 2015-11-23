/* 
 * File:   workerThread.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 20, 2015, 1:09 PM
 */

#ifndef WORKERTHREAD_H
#define	WORKERTHREAD_H

typedef struct {
    pthread_t *thread;
    int isWorking;
} workerT;

typedef struct {
    workerT *threads;
} vetorThreads;

#endif	/* WORKERTHREAD_H */

