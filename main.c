#include "sudokuController.h"

int main() {
    sudoku_t * sudoku = 0;
    int status = sudoku_starGame(sudoku);
    if(status == 0){
        board_print(sudoku->board);
    }
    return 0;
}
