//
// Created by maleal on 9/1/19.
//

#include "sudokuController.h"
#include "socket.h"

void startServer(char *port);

void startClient(char *hostName, char *port);

void sudoku_loadBoard(sudoku_t * self, FILE * input){
    board_init(self->board, input);
}

int sudoku_starGame(sudoku_t * self){
    FILE * input; // Acordarse de cerrarlo
    input = fopen("board.txt", "r");
    if (input == NULL) {
        perror("Error opening file");
        return ERROR;
    } else {
        sudoku_loadBoard(self, input);
    } 
    return SUCCESS;
}

int processMode(char * arguments[]){
    //procesar si es modo cliente o servidor
    if(arguments[1] == "server"){
        startServer(arguments[2]);
    } else if(arguments[1] == "client"){
        startClient(arguments[2], arguments[3]);
    }else{
        perror("Mode unidentified");
        return 1;
    }
}

void startClient(char *hostName, char *port) {
    

}

void startServer(char *port) {

}




