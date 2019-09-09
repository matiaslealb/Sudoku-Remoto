//
// Created by Matias Leal Bazterrica on 09/09/2019.
//
#define ERROR 1
#define SUCCESS 0
#ifndef SUDOKU_REMOTO_CLIENT_H
#define SUDOKU_REMOTO_CLIENT_H

#include "socket.h"

//Symbolic abstraction of sockets
typedef struct {
    socket_t socket;
} client_t;

int client_startClient(client_t * client, const char * host, const char * service);
#endif //SUDOKU_REMOTO_CLIENT_H
