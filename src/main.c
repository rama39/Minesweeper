#include <stdio.h>
#include <stdlib.h>

#define p 0.1
#define MAX 1000000

#define line(l) printf("+"); for(int i = 0; i < (l); i++) printf("--+"); printf("\n");

typedef struct cell {
    short int count;
    char has_bomb;
    char revealed;
} Cell;

char print_cell(Cell cell, char reveal) {
    if(!cell.revealed && !reveal)  return '#';
    if(cell.has_bomb)   return 'X';
    if(cell.count == 0) return ' ';
    return '0' + cell.count;
}

void print_board(int w, int h, Cell **board) {
    printf("   "); line(w)
    printf("   |"); for(int i = 0; i < w; i++) printf("%c |", 'A'+i); printf("\n");
    line(w+1)
    for(int i = 0; i < h; i++) {
        printf("|%c |", 'A'+i);
        for(int j = 0; j < w; j++) printf("%c |", print_cell(board[i][j], 0));
        printf("\n");
    }
    line(w+1)
}

void fill_board(int w, int h, Cell **board) {
    srand(69);
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) 
            board[i][j].has_bomb = ((float)(rand() % MAX) / MAX) < p;
}

void count_board(int w, int h, Cell **board) {
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) 
            for(int k = -1; k <= 1; k++)
                for(int l = -1; l <= 1; l++)
                    if(i+k >= 0 && i+k < h && j+l >= 0 && j+l < w)
                        board[i][j].count += (board[i+k][j+l].has_bomb ? 1 : 0);
}

void print_count(int w, int h, Cell **board) {
    printf("   "); line(w)
    printf("   |"); for(int i = 0; i < w; i++) printf("%c |", 'A'+i); printf("\n");
    line(w+1)
    for(int i = 0; i < h; i++) {
        printf("|%c |", 'A'+i);
        for(int j = 0; j < w; j++) printf("%c |", print_cell(board[i][j], 1));
        printf("\n");
    }
    line(w+1)
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

    Cell **board = malloc(sizeof(Cell*)*h);
    for (int i = 0; i < h; i++) board[i] = calloc(w, sizeof(Cell));
    
    fill_board(w, h, board);
    count_board(w, h, board);

    print_board(w, h, board);
    //print_count(w, h, board);

    for(int i = 0; i < h; i++) free(board[i]);
    free(board);
    return 0;
}