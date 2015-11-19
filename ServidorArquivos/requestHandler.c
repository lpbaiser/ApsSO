#include "connection.h"
#include "dynamicList.h"
#include <string.h>
#include "requestHandler.h"

#define BUFFER_SIZE 2048





void getRequest(connection_t connection,List *requestBuffer) {
    
    uint8_t buffer[BUFFER_SIZE];
    requestHandler request;
    char* req;
    request->connection=connection;
    //A idéia de um servidor echo é simplesmente mandar de volta a mensagem recebida
    while (1) {
        //aguardar a mensagem
        CONN_receive(connection, buffer, BUFFER_SIZE, 0);

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
        
        addLastList(requestBuffer,request);

        //        //imprimir a mensagem recebida e o tamanho da mensagem
        //        printf("recebi '%s' do cliente (%s:%s)... (len = %d)\n", 
        //                buffer,
        //                CONN_getPeerName(connection),
        //                CONN_getPeerPort(connection),
        //                strlen(buffer));
        //        
        //        //enviar de volta a mensagem recebida.
        //        CONN_send(connection, buffer, strlen(buffer)+1, 0);

        //detectar se a mensagem "sair" foi enviada.. se sim, fechar o servidor
        if (!strcmp(buffer, "sair")) {
            break;
        }
    }
}




