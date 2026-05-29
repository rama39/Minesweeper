#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int bomb_total = fill_board(board), reveal_total = 0, flag_total = 0;

    // Runs game until end condition
    // TODO: save files
    int x, y;
    char buffer[128];
    time_t start = time(NULL);
    while(1) {
        printf("BOMBS: | %i / %i |\n", bomb_total - flag_total, bomb_total);
        print_board(board, 0);
        
        printf("x y: ");
        fgets(buffer, 128, stdin);

        if(buffer[0] == 'X') {
            if(sscanf(buffer+1, " %i %i", &x, &y) != 2) continue;
            if(!(y >= 0 && y < board.h && x >= 0 && x < board.w)) continue;
            if(board._[y][x].revealed) continue;
            if(board._[y][x].flagged) board._[y][x].flagged = 0, flag_total--;
            else board._[y][x].flagged = 1, flag_total++;
            continue;
        } else {
            if(sscanf(buffer, " %i %i", &x, &y) != 2) continue;
            if(!(y >= 0 && y < board.h && x >= 0 && x < board.w)) continue;
            if(board._[y][x].flagged) continue;
            reveal_total += reveal(board, x, y);
        }

        if(board._[y][x].has_bomb) {
            printf("X_X You lost...\n");
            break;
        }
        if(board.w*board.h - reveal_total == bomb_total) {
            printf("B) You won in %li seconds!\n", time(NULL) - start);
            break;
        }
    }

    // Shows final board
    print_board(board, 1);

    // Clear board
    delete_board(board);
    return 0;
}