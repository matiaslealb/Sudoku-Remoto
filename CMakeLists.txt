cmake_minimum_required(VERSION 3.14)
project(Sudoku_Remoto C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c board.c sudokuController.c socket.c server.c client.c)
add_executable(Sudoku_Remoto ${SOURCE_FILES})
