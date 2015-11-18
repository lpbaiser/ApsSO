/* 
 * File:   request.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 17, 2015, 1:40 PM
 */

#ifndef REQUEST_H
#define	REQUEST_H

#include "connection.h"

typedef struct {
    int typeRequest;
    char path[2048];
    connection_t* connection;
}request;
