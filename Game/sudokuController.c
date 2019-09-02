//
// Created by maleal on 9/1/19.
//

#include "sudokuController.h"

void loadBoard(sudoku_t self, FILE * input){
    board_init(self.board, input);
}


