#include <stdlib.h>
#include "board.h"

Board *new_board(int n, int m) {
    Board *board = (Board*)malloc(sizeof(Board));
    if (board == NULL) {
        printf("Board cannot be initialized");
        return NULL;
    }
    int i;
    // allocate all the cells
    if ((board->cells = (int**)calloc(n, sizeof(int*))) == NULL) {
        printf("Board cannot be initialized");
        return NULL;
    }
    for (i=0; i<n; i++) {
        if ((board->cells[i] = (int*)calloc(m, sizeof(int))) == NULL) {
        printf("Board cannot be initialized");
            return NULL;
        }
    }
    board->n = n;
    board->m = m;
    board.


}