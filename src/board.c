
// Defining types

typedef struct Cell {
    short int count;
    char has_bomb;
    char revealed;
} Cell;

typedef struct Board {
    Cell **_;
    int w, h;
} Board;

Board new_board(int w, int h) {
    Board temp = {
        ._ = malloc(sizeof(Cell*)*h),
        .w = w, .h = h
    };
    for (int i = 0; i < h; i++) temp._[i] = calloc(w, sizeof(Cell));
    return temp;
}
void delete_board(Board board) {
    for(int i = 0; i < board.h; i++) free(board._[i]);
    free(board._);
}

// Printing functions

#define line(l) printf("+"); for(int i = 0; i < (l); i++) printf("--+"); printf("\n");
char print_cell(Cell cell, char reveal) {
    if(!cell.revealed && !reveal)  return '#';
    if(cell.has_bomb)   return 'X';
    if(cell.count == 0) return ' ';
    return '0' + cell.count;
}

void print_board(Board board, char end) {
    printf("   "); line(board.w)
    printf("   |"); for(int i = 0; i < board.w; i++) printf("%2i|", i); printf("\n");
    line(board.w+1)
    for(int i = 0; i < board.h; i++) {
        printf("|%2i|", i);
        for(int j = 0; j < board.w; j++) printf("%c |", print_cell(board._[i][j], end));
        printf("\n");
    }
    line(board.w+1)
}

// Compute board

#define p 0.1
#define MAX 1000000
int fill_board(Board board) {
    srand(69);
    int bomb_total = 0;
    for(int i = 0; i < board.h; i++)
        for(int j = 0; j < board.w; j++) {
            if (((float)(rand() % MAX) / MAX) >= p) continue;
            bomb_total += board._[i][j].has_bomb = 1;

            for(int k = -1; k <= 1; k++)
                for(int l = -1; l <= 1; l++)
                    if(i+k >= 0 && i+k < board.h && j+l >= 0 && j+l < board.w)
                        board._[i+k][j+l].count += 1;
        }
    return bomb_total;
}