//
// Created by maleal on 8/31/19.
//

#include "board.h"

void board_print(board_t * self){
    int rowMatrix = 0;
    for (int row = 0; row < 19; ++row) {
        if (row == 2 || row == 4 || row == 8 || row == 10 || row == 14 || row == 16 ){
            board_printHorizontalSlimBorder();
        }
        else if (row == 0 || row == 6 || row == 12 || row == 18){
            board_printHorizontalFatBorder();
        } else{
            board_printNumbers(self, rowMatrix);
            ++rowMatrix;
        }
    }
}

void board_printNumbers(board_t * self, int rowMatrix) {
   int columnMatrix = 0;
    for (int column = 0; column < 37; ++column) {
        if (column == 0 || column == 12 || column == 24){
            printf("U");
        }
        else if (column == 36){
            printf("U\n");
        }
        else if (column == 4 || column == 8 || column == 16 || column == 20
        || column == 28 || column == 32){
            printf("|");
        }
        else if(column == 2 || column == 6 || column == 10 || column == 14 || column == 18
        || column == 22 || column == 26|| column == 30 || column == 34){
            char testToPrint = self->playersBoard[rowMatrix][columnMatrix];
            printf("%c",testToPrint);
            ++columnMatrix;
        }else{
            printf(" ");
        }
    }
}

void board_printHorizontalSlimBorder() {
    printf("U---+---+---U---+---+---U---+---+---U\n");
}

void board_printHorizontalFatBorder() {
    printf("U===========U===========U===========U\n");
}

void board_clean(board_t * self){
    for (int row = LOWER_LIMIT_MATRIX; row < UPPER_LIMIT_MATRIX; ++row) {
        for (int column = 0; column < UPPER_LIMIT_MATRIX; ++column) {
            if (!board_isAnOriginalNumber(self, row, column)){
                self->originalBoard[row][column] = 0;
            }
        }
    }
}

bool board_isAnOriginalNumber(board_t * self, int row, int column){
    if (self->playersBoard[row][column] == self->originalBoard[row][row]) {
        return true;
    }
    return false;
}

bool board_addNumber(board_t * self, char number, int row, int column){
    if (self->playersBoard[row][column] == 0){
        self->playersBoard[row][column] = number;
        return true;
    }
    return false;
}

bool board_eraseNumber(board_t * self, int row, int column){
    if (!board_isAnOriginalNumber(self, row, column)){
        self->playersBoard[row][column] = 0;
        return true;
    }
    return false;
}

bool board_verifyLine(char line[]) {
    int numbersSeen[9];
    bool verified = true;
    int i = 0;
    while (verified){
        for (int j = LOWER_LIMIT_MATRIX; j < UPPER_LIMIT_MATRIX; ++j) {
            if (line[i] != 0 && line[i] == numbersSeen[j]){
                verified = false;
            }
        }
        numbersSeen[i] = line[i];
        i++;
    }
    return verified;
}

bool board_verifyRows(const board_t * self) {
    for (int row = LOWER_LIMIT_MATRIX; row < UPPER_LIMIT_MATRIX; ++row) {
        char rowToTest[9];
        for (int column = 0; column < 9; ++column)
        {
           rowToTest[column] = self->playersBoard[row][column];
        }
        if(!board_verifyLine(rowToTest)){
            return false;
        }
    }
    return true;
}

bool board_verifyColumns(const board_t * self) {
    for (int column = LOWER_LIMIT_MATRIX; column < UPPER_LIMIT_MATRIX; ++column) {
        char columnToTest[9];
        for (int row = LOWER_LIMIT_MATRIX; row < UPPER_LIMIT_MATRIX; ++row) {
            columnToTest[row] = self->playersBoard[row][column];
            if(!board_verifyLine(columnToTest)){
                return false;
            }
        }
    }
    return true;
}

bool board_verifyAreas(board_t * self) {
    for (int column = LOWER_LIMIT_MATRIX; column < 6; column = column + 3) {
        for (int row = LOWER_LIMIT_MATRIX; row < 6; row = row + 3) {
            if(!board_verifyArea(self,row, column)){
                return false;
            }
        }
    }
    return true;
}

bool board_verifyArea(board_t * self, int startRow, int startColumn) {
    int areaLenght = 0;
    char area[9];
    for (int row = startRow; row < startRow+3; ++row) {
        for (int column = startColumn; column < startColumn+3; ++column) {
            area[areaLenght] = self->playersBoard[row][column];
            ++areaLenght;
        }
    }
    return board_verifyLine(area);
}

bool board_verify(board_t * self){
    bool verified = true;
    while (verified){
        if(!board_verifyRows(self)){
            verified = false;
            break;
        }
        if(!board_verifyColumns(self)){
            verified = false;
            break;
        }
        if(!board_verifyAreas(self)){
           verified = false;
           break;
        }
    }
    return verified;
}

void board_init(board_t * self, FILE * file) {
    for (int row = LOWER_LIMIT_MATRIX; row < UPPER_LIMIT_MATRIX; ++row) {
        for (int column = LOWER_LIMIT_MATRIX; column < 10; ++column) {
            char number = getc(file);
            if (number != '\n') {
                self->originalBoard[row][column] = number;
                self->playersBoard[row][column] = number;
            }
        }
    }
}


