#include "ai_nim.h"
#include "game.h"

static int calculate_nim_sum(Board board);

void calculate_next_best_move(Move *new_move, Board current_board){
    int nim_sum, i;
    nim_sum = calculate_nim_sum(current_board);
    if (nim_sum != 0) {
        // find the first heap that its value is greater than its xor with nim sum.
        for (i=0; i < current_board.num_of_heaps; i++) {
            if ((current_board.heaps[i] ^ nim_sum) < current_board.heaps[i]) {
                *new_move = (Move){.heap_num = i, .num_of_objects = current_board.heaps[i] - (nim_sum ^ current_board.heaps[i])};
                return;
            }
        }
    } else {
        // find the first heap that has at least one object in it
        for (i=0; i < current_board.num_of_heaps; i++) {
            if (current_board.heaps[i] > 0) {
                *new_move = (Move){.heap_num = i, .num_of_objects = 1};
                return;
            }
        }
    }
}

static int calculate_nim_sum(Board board) {
    int i, result = 0;
    for (i=0; i < board.num_of_heaps; i++){
        result ^= board.heaps[i];
    }
    return result;
}



