#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    int w, h;

    if (argc == 3) {
        w = atoi(argv[1]), h = atoi(argv[2]);
    } else if (argc == 1) {
        printf("Width: ");
        scanf(" %i", &w);
        printf("Height: ");
        scanf(" %i", &h);
    } else {
        printf("Usage:\n  ./minesweeper\n    Width: [board width]\n    Height: [board height]\n  ./minesweeper [board width] [board height]\nObs: minimun size = 8\n");
    }
    if(w<8)w=8;
    if(h<8)h=8;
    printf("Width: %i\nHeight: %i\n", w, h);

    char board[h][w];

    return 0;
}