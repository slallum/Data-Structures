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


#endif /* SCORING_H_ */
