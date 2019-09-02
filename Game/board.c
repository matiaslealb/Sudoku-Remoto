//
// Created by maleal on 8/31/19.
//

#include "board.h"

const char * board_print(board_t * self){

}

void board_clean(board_t * self){
    for (int row = 0; row < 9; ++row) {
        for (int column = 0; column < 9; ++column) {
            if (!board_isAnOriginalNumber(self, row, column)){
                self->originalBoard[row][column] = 0;
            }
        }
    }
}

bool board_isAnOriginalNumber(board_t * self, char row, char column){
    if (self->playersBoard[row][column] == self->originalBoard[row][row]) {
        return true;
    }
    return false;
}

bool board_addNumber(board_t * self, char number, char row, char column){
    if (self->playersBoard[row][column] == 0){
        self->playersBoard[row][column] = number;
        return true;
    }
    return false;
}

bool board_eraseNumber(board_t * self, char row, char column){
    if (!board_isAnOriginalNumber(self, row, column)){
        self->playersBoard[row][column] = 0;
        return true;
    }
    return false;
}

bool board_verifyLine(char line[9]) {
    char numbersSeen[9];
    bool verified = true;
    int i = 0;
    while (verified){
        for (int j = 0; j < 9; ++j) {
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
    for (int row = 0; row < 9; ++row) {
        if(!board_verifyLine(self->playersBoard[row])){
            return false;
        }
    }
    return true;
}

bool board_verifyColumns(const board_t * self) {
    for (int column = 0; column < 9; ++column) {
        char columnToTest[9];
        for (int row = 0; row < 9; ++row) {
            columnToTest[row] = self->playersBoard[row][column];
            if(!board_verifyLine(columnToTest)){
                return false;
            }
        }
    }
    return true;
}

bool board_verifyAreas(board_t * self) {
    for (int column = 0; column < 6; column = column + 3) {
        for (int row = 0; row < 6; row = row + 3) {
            if(!board_verifyArea(self,row, column)){
                return false;
            }
        }
    }
    return true;
}

bool board_verifyArea(board_t * self, char startRow, char startColumn) {
    char areaLenght = 0;
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

void board_init(board_t * self, FILE * file){
    for (int row = 0; row < 9; ++row) {
        for (int column = 0; column < 9; ++column) {
            char number = getc(file);
            self->originalBoard[row][column] = number;
            self->playersBoard[row][column] = number;
        }
    }
}


