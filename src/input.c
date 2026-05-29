
Board receive_board(int argc, char **argv) {
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

    Board board = new_board(w, h);
    board.bomb_total = fill_board(board), board.reveal_total = 0, board.flag_count = 0;

    // Creates blank board to return
    return board;
}

int receive_command(Board *board, int start) {
    int x, y;
    static char buffer[128];
    printf("x y: ");
    fgets(buffer, 128, stdin);

    if(buffer[0] == 'X') {
        if(sscanf(buffer+1, " %i %i", &x, &y) != 2) return 1;
        if(!(y >= 0 && y < board->h && x >= 0 && x < board->w)) return 1;
        if(board->_[y][x].revealed) return 1;
        if(board->_[y][x].flagged) board->_[y][x].flagged = 0, board->flag_count--;
        else board->_[y][x].flagged = 1, board->flag_count++;
        return 1;
    } else {
        if(sscanf(buffer, " %i %i", &x, &y) != 2) return 1;
        if(!(y >= 0 && y < board->h && x >= 0 && x < board->w)) return 1;
        if(board->_[y][x].flagged) return 1;
        board->reveal_total += reveal(*board, x, y);
    }
    
    if(board->_[y][x].has_bomb) {
        printf("X_X You lost...\n");
        return 0;
    }
    if(board->w*board->h - board->reveal_total == board->bomb_total) {
        printf("B) You won in %li seconds!\n", time(NULL) - start);
        return 0;
    }
}