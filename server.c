//
// Created by Matias Leal Bazterrica on 09/09/2019.
//

#include "server.h"

int server_startServer(server_t * server, const char * service){
    int status;
    socket_t socket;
    status = socket_initServerMode(server,service);
    if (status == ERROR){
        printf("Error starting socket\n");
        return ERROR;
    }
    server->socket = socket;
    return SUCCESS;
}

int server_acceptClient(socket_t * socketToAccept, int * fdToAccept){
    int status;
    status = socket_accept(socketToAccept, fdToAccept);
    if (status == 0){

    }
}