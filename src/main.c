#include <stdio.h>
#include <stdlib.h>

#define p 0.1
#define MAX 1000000

void print_board(int w, int h, char **board) {
    printf("+");
    for(int i = 0; i < w; i++) printf("--+");
    printf("\n");
    for(int i = 0; i < h; i++) {
        printf("|");
        for(int j = 0; j < w; j++) printf("%c |", board[i][j] ? 'X':' ');
        printf("\n");
    }
    printf("+");
    for(int i = 0; i < w; i++) printf("--+");
    printf("\n");
}

void fill_board(int w, int h, char **board) {
    srand(69);
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) 
            board[i][j] = ((float)(rand() % MAX) / MAX) < p;
}

void count_board(int w, int h, char **board, int **cboard) {
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) 
            for(int k = -1; k <= 1; k++)
                for(int l = -1; l <= 1; l++)
                    if(i+k >= 0 && i+k < h && j+l >= 0 && j+l < w)
                        cboard[i][j] += (board[i+k][j+l] ? 1 : 0);
}

void print_count(int w, int h, char **board, int **cboard) {
    printf("+");
    for(int i = 0; i < w; i++) printf("--+");
    printf("\n");
    for(int i = 0; i < h; i++) {
        printf("|");
        for(int j = 0; j < w; j++) printf("%c |", board[i][j] ? 'X': cboard[i][j] ? '0'+cboard[i][j] : ' ');
        printf("\n");
    }
    printf("+");
    for(int i = 0; i < w; i++) printf("--+");
    printf("\n");
}

int main(int argc, char **argv) {
    int w, h;

    if (argc == 3)
        w = atoi(argv[1]), h = atoi(argv[2]);
    else if (argc == 1)
        printf("Width: "),
        scanf(" %i", &w),
        printf("Height: "),
        scanf(" %i", &h);
    else
        printf("Usage:\n  ./minesweeper\n    Width: [board width]\n    Height: [board height]\n  ./minesweeper [board width] [board height]\nObs: minimun size = 8\n");
    if(w<8)w=8; if(h<8)h=8;
    printf("Width: %i\nHeight: %i\n", w, h);

    char **board = malloc(sizeof(char*)*h);
    for (int i = 0; i < h; i++) board[i] = malloc(sizeof(char)*w);
    int **cboard = malloc(sizeof(int*)*h);
    for (int i = 0; i < h; i++) cboard[i] = calloc(w, sizeof(int));
    
    fill_board(w, h, board);
    count_board(w, h, board, cboard);

    print_board(w, h, board);
    print_count(w, h, board, cboard);

    for(int i = 0; i < h; i++) free(board[i]);
    free(board);
    for(int i = 0; i < h; i++) free(cboard[i]);
    free(cboard);
    return 0;
}