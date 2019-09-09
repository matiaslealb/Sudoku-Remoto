//
// Created by Matias Leal Bazterrica on 09/09/2019.
//

#include "client.h"

int client_startClient(client_t * client, const char * host, const char * service){
    int status;
    socket_t socket;
    status = socket_init(&socket, host, service);
    if(status == ERROR){
        printf("Error starting socket\n");
        return ERROR;
    }
    client->socket = socket;
    return SUCCESS;
}

