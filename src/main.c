#include <stdio.h>
#include <stdlib.h>

#define p 0.1
#define MAX 1000000

#define line(l) printf("+"); for(int i = 0; i < (l); i++) printf("--+"); printf("\n");

typedef struct Cell {
    short int count;
    char has_bomb;
    char revealed;
} Cell;

typedef struct Board {
    Cell **_;
    int w, h;
} Board;

char print_cell(Cell cell, char reveal) {
    if(!cell.revealed && !reveal)  return '#';
    if(cell.has_bomb)   return 'X';
    if(cell.count == 0) return ' ';
    return '0' + cell.count;
}

void print_board(Board board, char end) {
    printf("   "); line(board.w)
    printf("   |"); for(int i = 0; i < board.w; i++) printf("% 2i|", i); printf("\n");
    line(board.w+1)
    for(int i = 0; i < board.h; i++) {
        printf("|% 2i|", i);
        for(int j = 0; j < board.w; j++) printf("%c |", print_cell(board._[i][j], end));
        printf("\n");
    }
    line(board.w+1)
}

int fill_board(Board board) {
    srand(69);
    int bomb_total = 0;
    for(int i = 0; i < board.h; i++)
        for(int j = 0; j < board.w; j++) 
            bomb_total += board._[i][j].has_bomb = ((float)(rand() % MAX) / MAX) < p;
    return bomb_total;
}

void count_board(Board board) {
    for(int i = 0; i < board.h; i++)
        for(int j = 0; j < board.w; j++) 
            for(int k = -1; k <= 1; k++)
                for(int l = -1; l <= 1; l++)
                    if(i+k >= 0 && i+k < board.h && j+l >= 0 && j+l < board.w)
                        board._[i][j].count += (board._[i+k][j+l].has_bomb ? 1 : 0);
}

int _aux_DFS(Board board, int x, int y, char ** visited) {
    //printf("%i %i\n", x, y);
    if(!(y >= 0 && y < board.h && x >= 0 && x < board.w)) return 0;
    if(board._[y][x].revealed) return 0;
    board._[y][x].revealed = 1;
    visited[y][x] = 1;
    if (board._[y][x].count > 0) return 1;

    int branch_total = 0;
    for(int k = -1; k <= 1; k++)
        for(int l = -1; l <= 1; l++) 
            branch_total += _aux_DFS(board, x+l, y+k, visited);
    return 1 + branch_total;
}
int DFS_reveal(Board board, int x, int y) {
    char **visited = malloc(sizeof(char*)*board.h);
    for (int i = 0; i < board.h; i++) visited[i] = calloc(board.w, sizeof(char));
    
    int reveal_count = _aux_DFS(board, x, y, visited);

    for(int i = 0; i < board.h; i++) free(visited[i]);
    free(visited);

    return reveal_count;
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
        printf("Usage:\n  ./minesweeper\n    Width: [board width]\n    Height: [board height]\n  ./minesweeper [board width] [board height]\nObs: minimun size = 8\n"),
        exit(0);
    if(w<8)w=8; if(h<8)h=8;
    printf("Width: %i\nHeight: %i\n", w, h);

    Board board = {
        ._ = malloc(sizeof(Cell*)*h),
        .w = w, .h = h
    };
    for (int i = 0; i < h; i++) board._[i] = calloc(w, sizeof(Cell));
    
    int bomb_total = fill_board(board), reveal_total = 0;
    count_board(board);

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
        if(w*h - reveal_total == bomb_total) {
            printf("B) You won!\n");
            break;
        }
        printf("reveal: %i\nbomb:%i\n", reveal_total, bomb_total);
    }

    print_board(board, 1);

    for(int i = 0; i < h; i++) free(board._[i]);
    free(board._);
    return 0;
}