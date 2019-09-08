//
// Created by maleal on 9/8/19.
#include <stdbool.h>
#include "socket.h"

int socket_send(socket_t * self, const void * buffer, size_t size){
    while (bytes_sent < request_len && is_there_a_socket_error == false && is_the_remote_socket_closed == false) {
        s = send(skt, &request[bytes_sent], request_len - bytes_sent, MSG_NOSIGNAL);

        if (s == -1) {  // ups,  hubo un error
            printf("Error: %s\n", strerror(errno));
            is_there_a_socket_error = true;
        }
        else if (s == 0) { // nos cerraron el socket :(
            is_the_remote_socket_closed = true;
        }
        else {
            bytes_sent += s;
        }
    }

    if (is_the_remote_socket_closed || is_there_a_socket_error) {
        shutdown(skt, SHUT_RDWR);
        close(skt);
        return 1;
    }
}

int socket_receive(socket_t * socket, void * buffer, size_t size){
    while (is_there_a_socket_error == false && is_the_remote_socket_closed == false) {
        s = recv(skt, &response[bytes_recv], RESPONSE_MAX_LEN - bytes_recv - 1, 0);

        if (s == -1) {
            printf("Error: %s\n", strerror(errno));
            is_there_a_socket_error = true;
        }
        else if (s == 0) {
            // cerraron el socket del otro lado:
            // voy a asumir que nos dieron toda la respuesta (estoy simplificando esto)
            is_the_remote_socket_closed = true;
        }
        else {
            bytes_recv = s;

            response[bytes_recv] = 0;
            printf("%s", response);

            //reusamos el mismo buffer, no me interesa tener toda la
            //respuesta en memoria
            bytes_recv = 0;
        }
    }
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

}