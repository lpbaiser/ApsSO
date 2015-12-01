#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include "connection.h"

#define BUFFER_SIZE 1024

int main(int argc, char** argv) {

    //Conexão ao cliente
    connection_t* connection;

    //host do servidor e a porta a conectar
    char* host;
    char* port;

    //Buffer usado para receber e enviar dados
    char buffer[BUFFER_SIZE];
    char typeRequest[2];
    memset(typeRequest, '\0', sizeof(char)*2);

    //Verificar se a porta e o host foi passado como argumento
    if (argc < 3) {
        fprintf(stderr, "uso: %s host porta\n", argv[0]);
        return EXIT_FAILURE;
    }

    //Host é o primeiro argumento e porta o segundo.
    host = argv[1];
    port = argv[2];

    //Conectar ao servidor
    connection = CONN_connectTo((char*) host, (char*) port);

    //verificar se houve sucesso na conexão
    if (!connection) {
        fprintf(stderr, "Não foi possível conectar a %s:%s!\n", host, port);
        return (EXIT_FAILURE);
    }

    //Aguardar a mensagem de boas vindas e imprimi-la
    CONN_receive(connection, buffer, 1024, 0);
    printf("%s\n", buffer);

    //    CONN_receive(connection, typeRequest, 2, 0);
    //    CONN_receive(connection, buffer, BUFFER_SIZE, 0);
    //    printf("%s\n", buffer);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        printf("Digite uma requisição: \n>>> ");

        //ler a mensagem a ser enviada ao servidor
        fgets(buffer, BUFFER_SIZE, stdin);

        //subtituir \n por um terminador de string
        *(strstr(buffer, "\n")) = 0;

        //ter certeza que há um terminador de string no último caractere
        buffer[BUFFER_SIZE - 1] = 0;

        //enviar a mensagem
        CONN_send(connection, buffer, strlen(buffer) + 1, 0);

        //aguardar o echo
        CONN_receive(connection, typeRequest, 2, 0);
        if (!strcmp(typeRequest, "ls")) {
            memset(buffer, 0, BUFFER_SIZE);
            CONN_receive(connection, buffer, BUFFER_SIZE, 0);
            printf("Chegou request");
            printf("%s\n", buffer);

        } else if (!strcmp(typeRequest, "wg")) {
            memset(buffer, 0, BUFFER_SIZE);
            char nomeArquivo[BUFFER_SIZE];
            CONN_receive(connection, nomeArquivo, BUFFER_SIZE, 0);

            FILE *f;
            f = fopen(nomeArquivo, "w");

            do {

                CONN_receive(connection, buffer, BUFFER_SIZE, 0);
                int i;
                for (i = 0; i < strlen(buffer) - 1; i++) {
                    fputc(buffer[i], f);
                }

            } while (strcmp(buffer, "EOF"));

            fclose(f);
            //guardar arquivo no diretório
        }
        memset(typeRequest, '\0', sizeof(char)*2);
        //        else if (strcmp(typeRequest, "erro")) {
        //            CONN_receive(connection, buffer, BUFFER_SIZE, 0);
        //            printf("%s\n", buffer);
        //        }

        //verificar se enviou um "sair". Caso afirmativo, terminar o cliente.
        if (!strcmp(buffer, "sair")) {
            break;
        }
    }

    //fechar a conexão
    CONN_close(connection);

    return EXIT_FAILURE;

}


