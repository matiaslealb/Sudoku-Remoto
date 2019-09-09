//
// Created by maleal on 9/8/19.
#include <stdbool.h>
#include "socket.h"

int socket_send(socket_t * self, const char * request, size_t sizeOfRequest){
    int bytesSent = 0;
    int status = 0;
    while (bytesSent < sizeOfRequest ) {
        status = send(self->fileDescriptor, &request[bytesSent], sizeOfRequest - bytesSent, MSG_NOSIGNAL);
        if (status == -1) {
            printf("Error sending message");
            socket_release(self);
            return 1;
        }
        else if (status == 0) {
            printf("Socket was close");
            socket_release(self);
            return 1;
        }
        else {
            bytesSent += status;
        }
    }

}
// ver si maneja bien errores
int socket_receive(socket_t * socket, char * response, size_t sizeOfResponse){
    int status = 0;
    int bytesReceive = 0;
    bool connection = true;
    while (connection && sizeOfResponse > bytesReceive ) {
        status = recv(socket->fileDescriptor, &response[bytesReceive], sizeOfResponse - bytesReceive - 1, 0);
        if (status > 0) {
            bytesReceive = status;
            response[bytesReceive] = 0;
            bytesReceive = 0;
        }
        else {
            printf("Error receiving message");
            connection = false;
        }
    }
    return status;
}


void socket_release(socket_t * self){
    shutdown(self->fileDescriptor, SHUT_RDWR);
    close(self->fileDescriptor);
}

int socket_connect(socket_t * self){
    getBestFd(self);
    freeaddrinfo(self->address);
    if (self->fileDescriptor == -1) {
        printf("Error connecting to host");
        return 1;
    }

    return 0;
}

int socket_accept(socket_t * socketToAccept, int * fdToAccept){
    fdToAccept = accept(socketToAccept->fileDescriptor, NULL, NULL);
    if (fdToAccept == -1){
        printf("Error accepting socket");
        socket_release(socketToAccept);
        return 0;
    }
}

void getBestFd(socket_t * self) {
    struct addrinfo * addressToTest= NULL;
    bool connectionSuccess = false;
    int fileDescriptor = 0;

    for (addressToTest = self->address; addressToTest != NULL && connectionSuccess == false; addressToTest = addressToTest->ai_next) {
        fileDescriptor = socket(addressToTest->ai_family, addressToTest->ai_socktype, addressToTest->ai_protocol);
        int status = connect(fileDescriptor, addressToTest->ai_addr, addressToTest->ai_addrlen);
        if (status == -1) {
           printf("Error connecting host");
           close(fileDescriptor);
        }
        connectionSuccess = (fileDescriptor != -1);
    }
    self->fileDescriptor = fileDescriptor;
}

int socket_init(socket_t * self, const char * host, const char * service) {
    struct addrinfo hints;
    int status;
    self->host = host;
    self->service = service;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */
    status = getaddrinfo(self->host, self->service, &hints, self->address);
    if (status){
        printf("Fail to get address");
        return 1;
    }
    return 0;
}

int socket_bind_and_listen(socket_t * socketToBindAndListen){
    int status = 0;
    int fd;
    struct addrinfo *ptr = NULL;

    fd = socket(socketToBindAndListen->address->ai_family, socketToBindAndListen->address->ai_socktype, socketToBindAndListen->address->ai_protocol);
    if(fd == -1){
        printf("Error getting file descriptor");
        return 1;
    }
    socketToBindAndListen->fileDescriptor = fd;
    status = bind(socketToBindAndListen->fileDescriptor, socketToBindAndListen->address->ai_addr, socketToBindAndListen->address->ai_addrlen);
    if (status == -1) {
        printf("Error binding");
        close(socketToBindAndListen->fileDescriptor);
        freeaddrinfo(ptr);
        return 1;
    }
    freeaddrinfo(ptr);
    status = listen(socketToBindAndListen->fileDescriptor, 20);
    if (status == -1) {
        printf("Error listening");
        close(socketToBindAndListen->fileDescriptor);
        return 1;
    }

    return 0;
}

