/*
 * scoring.h
 *
 *  Created on: Dec 21, 2013
 *      Author: shir
 */

#ifndef SCORING_H_
#define SCORING_H_

/**
 * Scoring function for the connect4 game
 * Each 4 disc span recieves a score and the number
 * of spans for each score are calculated.
 * The outcome vector is multiplied by a weight vector
 */
int connect4_scoring(int** board, int n, int m);

/**
 * Goes over all horizontal spans on board.
 * For each row, calcs first span and then just updates each step
 */
void count_horizontal(int *spans_count, int** board, int n, int m);

/**
 * Goes over all vertical spans on board.
 * For each coloumn, calcs first span and then just update each step.
 */
void count_vertical(int *spans_count, int** board, int n, int m);

/**
 * Goes over all diagonal spans on board.
 * First goes over 'forward' diagonals, then 'backward' ones.
 */
void count_diagonal(int *spans_count, int** board, int n, int m);

#endif /* SCORING_H_ */
