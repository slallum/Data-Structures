/*
 * MacCos.c
 *
 *  Created on: Oct 22, 2013
 *      Author: shir
 */

#include <stdio.h>

int main(void) {

	double x;
	unsigned int N;
	float current = 1;
	double result = 0;
	int n;

	printf("Enter a double number and a non-negative integer:\n");
	scanf("%lf %u", &x, &N);

	for (n = 0; n < N; n++) {
		if (n % 4 == 0) {
			result += current;
		} else if (n % 4 == 2) {
			result -= current;
		}
		current *= (x / (n+1));
	}
	printf("The %d-th order Maclaurin polynomial function at x=%lf is %lf\n", N, x, result);
	return 0;
}
