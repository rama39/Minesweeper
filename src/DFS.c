int _aux_DFS(Board board, int x, int y, char ** visited) {
    //printf("%i %i\n", x, y);
    if(!(y >= 0 && y < board.h && x >= 0 && x < board.w)) return 0;
    if(board._[y][x].revealed || board._[y][x].flagged) return 0;
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

int reveal(Board board, int x, int y) {
    if(!(y >= 0 && y < board.h && x >= 0 && x < board.w)) return 0;
    if(board._[y][x].revealed) {
        if(board._[y][x].count > 0) {
            int neighbour_flags = 0;
            for(int k = -1; k <= 1; k++)
            for(int l = -1; l <= 1; l++) 
                if(get(board, x+l, y+k).flagged) 
                    neighbour_flags++;

            if(neighbour_flags == board._[y][x].count) {
                int neighbour_reveal = 0;
                for(int k = -1; k <= 1; k++)
                for(int l = -1; l <= 1; l++) 
                    if(!get(board, x+l, y+k).flagged && !get(board, x+l, y+k).revealed)
                        neighbour_reveal += DFS_reveal(board, x+l, y+k);
                return neighbour_reveal;
            }
        }
        return 0;
    } else return DFS_reveal(board, x, y);
}