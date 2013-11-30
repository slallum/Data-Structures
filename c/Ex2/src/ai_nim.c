#include "ai_nim.h"
#include "game.h"


Move calculate_next_best_move(Board current_board){
    int nim_sum, i;
    nim_sum = calculate_nim_sum(current_board);
    if (nim_sum != 0) {
        for (i=0; i < current_board.num_of_heaps; i++) {
            if ((current_board.heaps[i] ^ nim_sum) < current_board.heaps[i]) {
                return (Move){.heap_num = i, .num_of_objects = current_board.heaps[i] - (nim_sum ^ current_board.heaps[i])};
            }
        }
    } else {
        for (i=0; i < current_board.num_of_heaps; i++) {
            if (current_board.heaps[i] > 0) {
                return (Move){.heap_num = i, .num_of_objects = 1};
            }
        }
    }
    // i don't really want to return here anything, what should we do?
    return (Move){.heap_num = 1, .num_of_objects = 1};
}


// TODO: static?
int calculate_nim_sum(Board board) {
    int i, result = 0;
    for (i=0; i < board.num_of_heaps; i++){
        result ^= board.heaps[i];
    }
    return result;
}



