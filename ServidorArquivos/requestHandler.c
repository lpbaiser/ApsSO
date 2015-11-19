#include "connection.h"
#include "dynamicList.h"

#include "request.h"

#define BUFFER_SIZE 2048


List* requestBuffer;

void getRequest(connection_t connection) {

    uint8_t buffer[BUFFER_SIZE];
    
     //A idéia de um servidor echo é simplesmente mandar de volta a mensagem recebida
    while(1){
        //aguardar a mensagem
        CONN_receive(connection, buffer, BUFFER_SIZE, 0);
        
        int tamBuffer = len(buffer);
        while ()

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
        if(!strcmp(buffer, "sair")){
            break;
        }
    }   
}




