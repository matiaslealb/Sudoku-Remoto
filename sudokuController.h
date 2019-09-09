//
// Created by maleal on 9/1/19.
//
#define ERROR 1
#define SUCCESS 0
#ifndef SUDOKU_REMOTO_SUDOKUCONTROLLER_H
#define SUDOKU_REMOTO_SUDOKUCONTROLLER_H
#include <stdio.h>
#include "board.h"
#include "server.h"
#include "client.h"

typedef struct {
    board_t * board;
} sudoku_t;

void sudoku_loadBoard(sudoku_t * self, FILE * input);

int sudoku_starGame(sudoku_t * self);

void sudoku_manageGame(sudoku_t *sudoku, server_t *server);

void sudoku_manageGame(sudoku_t *sudoku, server_t *server);

void sudoku_playGame(client_t *client);

int sudoku_setUpClient(char *const *arguments);

int sudoku_setUpServer(const char * service);

void sudoku_playGame(client_t *client);

void sudoku_analyzeResponse(char * response, sudoku_t * sudoku);

int processMode(char * arguments[]);

#endif //SUDOKU_REMOTO_SUDOKUCONTROLLER_H
