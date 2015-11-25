/* 
 * File:   workerThread.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 20, 2015, 1:09 PM
 */

#ifndef WORKERTHREAD_H
#define	WORKERTHREAD_H

void processLs(Request *r);

void processWget(Request *r);

void wakeThread();

#endif	/* WORKERTHREAD_H */

