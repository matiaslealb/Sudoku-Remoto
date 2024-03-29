//
// Created by maleal on 8/31/19.
//

#ifndef SUDOKU_REMOTO_BOARD_H
#define SUDOKU_REMOTO_BOARD_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char originalBoard[9][9];
    char playersBoard[9][9];
} board_t;

static const int LOWER_LIMIT_MATRIX = 0;

static const int UPPER_LIMIT_MATRIX = 9;

void board_print(board_t * self);

void board_clean(board_t * self);

void board_printHorizontalFatBorder();

void board_printHorizontalSlimBorder();

void board_printNumbers(board_t *self, int rowMatrix);

bool board_addNumber(board_t * self, char number, int row, int column);

bool board_eraseNumber(board_t * self, int row, int column);

bool board_isAnOriginalNumber(board_t * self, int row, int column);

bool board_verify(board_t * self);

bool board_verifyLine(char line[9]);

bool board_verifyRows(const board_t * self);

bool board_verifyColumns(const board_t * self);

bool board_verifyAreas(board_t * self);

bool board_verifyArea(board_t * self, int startRow, int startColumn);

void board_init(board_t * self, FILE * file);

#endif //SUDOKU_REMOTO_BOARD_H
