/*
 * MacCos_limit.c
 *
 *  Created on: Oct 27, 2013
 *      Author: shir
 */
#include <stdio.h>

int main(void) {

	double x;
	unsigned int N = 0;
	double current = 1;

	printf("Enter a double number:\n");
	scanf("%lf", &x);

	while (current != 0) {
		N += 1;
		current *= (x / N);
	}

	printf("The optimal order of the Maclaurin polynomial function at x=%lf is %u\n", x, N-1);
	return 0;
}

