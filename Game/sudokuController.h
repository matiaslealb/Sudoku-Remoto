//
// Created by maleal on 9/1/19.
//

#ifndef SUDOKU_REMOTO_SUDOKUCONTROLLER_H
#define SUDOKU_REMOTO_SUDOKUCONTROLLER_H
#include <stdio.h>
#include "board.h"

typedef struct {
    board_t *board;
}sudoku_t;

void loadBoard(sudoku_t self, FILE * input);

#endif //SUDOKU_REMOTO_SUDOKUCONTROLLER_H
