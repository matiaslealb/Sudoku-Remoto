//
// Created by maleal on 9/1/19.
//

#include "sudokuController.h"
#include "socket.h"
#include "server.h"
#include "client.h"


void sudoku_loadBoard(sudoku_t * self, FILE * input){
    board_init(self->board, input);
}

int sudoku_starGame(sudoku_t * self){
    FILE * input; // Acordarse de cerrarlo
    input = fopen("board.txt", "r");
    if (input == NULL) {
        perror("Error opening file\n");
        return ERROR;
    } else {
        sudoku_loadBoard(self, input);
    } 
    return SUCCESS;
}

int processMode(char * arguments[]){
    int status;
    if(strcmp(arguments[1],"server") == 0){
        status = sudoku_setUpServer(arguments[2]);
        if(status == 1){
            printf("Error setting up server\n");
            return ERROR;
        }
    } else if(strcmp(arguments[1],"client") == 0){
        sudoku_setUpClient(arguments);

    }else{
        printf("Modo no soportado, el primer parámetro debe ser server o client\n");
        return ERROR;
    }

    return SUCCESS;
}

int sudoku_setUpClient(char *const *arguments) {
    client_t client;
    int status;
    status = client_startClient(&client, arguments[2], arguments[3]);
    if(status == ERROR){
        printf("Error setting up Client\n");
    }
    sudoku_playGame(&client);
    return SUCCESS;
}

int sudoku_setUpServer(const char * service){
    server_t server;
    sudoku_t sudoku;
    int status;
    status = sudoku_starGame(&sudoku);
    if(status == ERROR){
        printf("Error starting sudoku\n");
        return ERROR;
    }
    status = server_startServer(&server, service);
    if(status == ERROR){
        socket_release(server.socket);
        printf("Error starting server\n");
        return ERROR;
    }
    sudoku_manageGame(&sudoku, &server);
    return SUCCESS;
}

void sudoku_playGame(client_t *client) {

}

void sudoku_manageGame(sudoku_t * sudoku, server_t *server) {
    int status;
    int fdToAccept;
    char response[5];
    size_t size = 5;
    bool isSomeoneThere = true;
    status = socket_accept(server->socket, &fdToAccept);
    if (status == 1){
        printf("Error accepting client");
    }
    while(isSomeoneThere){
        isSomeoneThere = socket_receive(server->socket, response, size);
        sudoku_analyzeResponse(response, sudoku);

    }


}

void sudoku_analyzeResponse(char * response, sudoku_t * sudoku) {
    switch (response[0]) {
        case 'V':
            return;
        case 'R':
            return;
        case 'G':
            return;
        case 'E':
            return;
        case 'P':
            return;
    }
}





