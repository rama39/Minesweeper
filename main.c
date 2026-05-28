#include <stdio.h>
#include <stdlib.h>

#include "src/minesweeper.h"

int main(int argc, char **argv) {

    // Safely receives Width and Height
    int w, h;
    if (argc == 3)
        w = atoi(argv[1]), h = atoi(argv[2]);
    else if (argc == 1)
        printf("Width: "),
        scanf(" %i", &w),
        printf("Height: "),
        scanf(" %i", &h);
    else
        printf("Usage:\n  ./minesweeper\n    Width: [board width]\n    Height: [board height]\n  ./minesweeper [board width] [board height]\nObs: minimun size = 8\n"),
        exit(0);
    if(w<8)w=8; if(h<8)h=8;
    printf("Width: %i\nHeight: %i\n", w, h);

    // Creates game board
    Board board = new_board(w, h);
    int bomb_total = fill_board(board), reveal_total = 0;

    // Runs game until end condition
    // TODO: count game time
    // TODO: save files
    // TODO: show bomb count
    // TODO: add flags
    int x, y;
    while(1) {
        print_board(board, 0);
        
        printf("x y: "),
        scanf(" %i %i", &x, &y);

        reveal_total += DFS_reveal(board, x, y);

        if(board._[y][x].has_bomb) {
            printf("X_X You lost...\n");
            break;
        }
        if(board.w*board.h - reveal_total == bomb_total) {
            printf("B) You won!\n");
            break;
        }
        printf("reveal: %i\nbomb:%i\n", reveal_total, bomb_total);
    }

    // Shows final board
    print_board(board, 1);

    // Clear board
    delete_board(board);
    return 0;
}