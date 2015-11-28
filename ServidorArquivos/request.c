/* 
 * File:   request.c
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 21, 2015, 5:57 PM
 */

#include "connection.h"
#include "request.h"
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

Request* createRequest(connection_t *connection, char* buffer) {

    Request *request = (Request*) malloc(sizeof(Request));
    char* req;
    req = malloc(sizeof(char));
    request->connection = connection;

    int tamBuffer = strlen(buffer);
    int i = 0;
    while (buffer[i] != ' ') {
        req[i] = buffer[i];
        i++;
    }
    i++;
    int j = 0;
    while (i < tamBuffer) {
        request->path[j] = buffer[i];
        i++;
        j++;
    }

    if (strcmp(req, "ls")) {
        request->typeRequest = 1;
    } else if (strcmp(req, "wget")) {
        request->typeRequest = 2;
    }

    return request;
}