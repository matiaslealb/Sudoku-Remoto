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
            perror("Error sending message");
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
            perror("Error receiving message");
            connection = false;
        }
    }
    return status;
}

void socket_init(socket_t * socket){
    socket->fileDescriptor = 0;
}

void socket_release(socket_t * self){
    shutdown(self->fileDescriptor, SHUT_RDWR);
    close(self->fileDescriptor);
}

int socket_connect(socket_t * self, const char * host, const char * service){
    int address = 0;
    int fileDescriptor = 0;
    struct addrinfo *result;
    struct addrinfo *ptr = NULL;
    getAddress(host, service, &address, &result);
    if (address != 0) {
        perror("Error getting address");
        return 1;
    }
    self->fileDescriptor = getBestFd(fileDescriptor, result, ptr);
    freeaddrinfo(result);
    if (self->fileDescriptor = -1) {
        return 1;
    }
}

int getBestFd(int fileDescriptor, struct addrinfo *result, struct addrinfo *ptr) {
    bool connectionSuccess = false;
    for (ptr = result; ptr != NULL && connectionSuccess == false; ptr = ptr->ai_next) {
        fileDescriptor = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        int status = connect(fileDescriptor, ptr->ai_addr, ptr->ai_addrlen);
        if (status == -1) {
           perror("Error connecting host");
           close(fileDescriptor);
        }
        connectionSuccess = (fileDescriptor != -1);
    }
    return fileDescriptor;
}

void getAddress(const char *host, const char *service, int *address, struct addrinfo **result) {
    struct addrinfo hints;
    struct addrinfo  *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */
    (*address) = getaddrinfo(host, service, &hints, result);
}

int socket_bind_and_listen(socket_t * self, const char * host, const char * service){
    int status = 0;
    struct addrinfo *ptr = NULL;
    status = bind(self->fileDescriptor, ptr->ai_addr, ptr->ai_addrlen);
    if (status == -1) {
        perror("Error binding");
        close(self->fileDescriptor);
        freeaddrinfo(ptr);
        return 1;
    }
    freeaddrinfo(ptr);
    status = listen(self->fileDescriptor, 20);
    if (status == -1) {
        perror("Error listening");
        close(self->fileDescriptor);
        return 1;
    }

    return 0;
}