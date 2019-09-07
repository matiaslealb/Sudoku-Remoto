//
// Created by maleal on 9/1/19.
//

#include "sudokuController.h"

void sudoku_loadBoard(sudoku_t * self, FILE * input){
    board_init(self->board, input);
}

int sudoku_starGame(sudoku_t * self){
    FILE * input;
    input = fopen("board.txt", "r");

    if (! input) {
        perror("Error");
        return ERROR;
    } else {
        sudoku_loadBoard(self, input);
    } 
    return SUCCESS;
}



