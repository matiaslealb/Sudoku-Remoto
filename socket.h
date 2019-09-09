//
// Created by maleal on 8/31/19.
//
#define ERROR 1
#define SUCCESS 0
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
    int fileDescriptor;
    struct addrinfo * address;
    const char * host;
    const char * service;
} socket_t;

int socket_send(socket_t * self, const char * request, size_t sizeOfRequest);

bool socket_receive(socket_t * socket, char * response, size_t sizeOfResponse);

void socket_release(socket_t * self);

int socket_connect(socket_t * self);

int socket_initServerMode(socket_t * self, const char * service);

int socket_initClientMode(socket_t * self, const char * host, const char * service);

int socket_bind_and_listen(socket_t * socketToBindAndListen);

int socket_init(socket_t * self, const char * host, const char * service);

void getBestFd(socket_t * self);

int socket_accept(socket_t * socketToAccept, int * fdToAccept);


#endif //SUDOKU_REMOTO_SOCKET_H
