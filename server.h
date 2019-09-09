//
// Created by Matias Leal Bazterrica on 09/09/2019.
//
#define ERROR 1
#define SUCCESS 0
#ifndef SUDOKU_REMOTO_SERVER_H
#define SUDOKU_REMOTO_SERVER_H

#include "socket.h"

//Symbolic abstraction of sockets
typedef struct {
    socket_t *socket;
} server_t;


int server_startServer(server_t * server, const char * service);

#endif //SUDOKU_REMOTO_SERVER_H
