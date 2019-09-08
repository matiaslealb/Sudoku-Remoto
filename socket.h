//
// Created by maleal on 8/31/19.
//

#ifndef SUDOKU_REMOTO_SOCKET_H
#define SUDOKU_REMOTO_SOCKET_H

#define _POSIX_C_SOURCE 200112L
#include <sys/types.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    int fileDescriptor
} socket_t;

int socket_send(socket_t * self, const void * buffer, size_t size);

int socket_receive(socket_t * socket, void * buffer, size_t size);

void socket_init(socket_t * socket);

void socket_release(socket_t * self);

int socket_connect(socket_t * self, const char * host, const char * service);

int socket_bind_and_listen(socket_t * self, const char * host, const char * service);

void getAddress(const char *host, const char *service, int *address, struct addrinfo **result);

int getBestFd(int fileDescriptor, struct addrinfo *result, struct addrinfo *ptr);

#endif //SUDOKU_REMOTO_SOCKET_H
