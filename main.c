#include "Game/sudokuController.h"

int main() {
    sudoku_t * sudoku = 0;
    sudoku_starGame(sudoku);

    board_print(sudoku->board);


    return 0;
}
