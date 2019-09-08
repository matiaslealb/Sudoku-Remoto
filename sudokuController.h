//
// Created by maleal on 9/1/19.
//
#define ERROR 1
#define SUCCESS 0
#ifndef SUDOKU_REMOTO_SUDOKUCONTROLLER_H
#define SUDOKU_REMOTO_SUDOKUCONTROLLER_H
#include <stdio.h>
#include "board.h"

typedef struct {
    board_t * board;
} sudoku_t;

void sudoku_loadBoard(sudoku_t * self, FILE * input);

int sudoku_starGame(sudoku_t * self);

void processMode(char * arguments);

#endif //SUDOKU_REMOTO_SUDOKUCONTROLLER_H
