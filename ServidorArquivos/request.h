/* 
 * File:   Request.h
 * Author: Leonardo Baiser <lpbaiser@gmail.com>
 *
 * Created on November 21, 2015, 5:57 PM
 */

#ifndef REQUEST_H
#define	REQUEST_H

typedef struct request{
    int typeRequest;
    char path[2048];
    struct connection_t* connection;
}Request;

/*Cria uma request de acordo com a entrada do usuario(ls ou wget)
 * e retorna para o request handler 
 */
Request* createRequest(connection_t connection, char* buffer);

#endif	/* REQUEST_H */

