#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lib/minesweeper.h"

int main(int argc, char **argv) {

    // Creates game board
    Board board = receive_board(argc, argv);

    // Runs game until end condition
    time_t start = time(NULL);
    int state = PLAY;
    do {
        printf("BOMBS: | %i / %i |\n", board.bomb_total - board.flag_count, board.bomb_total);

        print_board(board, 0);

        state = receive_command(&board);
        
    } while (state == PLAY);

    if(state == WIN)
        handle_victory(&board, time(NULL) - start);

    // Shows final board
    print_board(board, 1);

    // Clear board
    delete_board(board);
    return 0;
}