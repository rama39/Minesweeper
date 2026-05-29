#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/minesweeper.h"

int main(int argc, char **argv) {

    // Creates game board
    Board board = receive_board(argc, argv);

    // Runs game until end condition
    // TODO: save files
    time_t start = time(NULL);
    do {
        printf("BOMBS: | %i / %i |\n", board.bomb_total - board.flag_count, board.bomb_total);

        print_board(board, 0);
        
    } while (receive_command(&board, start));

    // Shows final board
    print_board(board, 1);

    // Clear board
    delete_board(board);
    return 0;
}