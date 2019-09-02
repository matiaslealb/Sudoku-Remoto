//
// Created by maleal on 8/31/19.
//

#ifndef SUDOKU_REMOTO_SOCKET_H
#define SUDOKU_REMOTO_SOCKET_H

#include <stddef.h>

typedef struct {
    int fileDescriptor
}socket_t;

int socket_send(socket_t * self, const void * buffer, size_t size);

int socket_receive(socket_t * socket, void * buffer, size_t size);

void socket_init(socket_t * socket);

void socket_release(socket_t * self);

void socket_connect(socket_t * self, const char * host, const char * service);

int socket_bind_and_listen(socket_t * self, const char * host, const char * service);

#endif //SUDOKU_REMOTO_SOCKET_H
