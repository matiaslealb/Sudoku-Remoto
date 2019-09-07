//
// Created by maleal on 9/1/19.
//

#include "sudokuController.h"

void sudoku_loadBoard(sudoku_t * self, FILE * input){
    board_init(self->board, input);
}

void sudoku_starGame(sudoku_t * self){
    FILE * input;
    input = fopen("board.txt", "r");
    sudoku_loadBoard(self, input);
}



