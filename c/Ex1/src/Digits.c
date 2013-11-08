#include <stdio.h>
#include <stdlib.h> 

#include <math.h>

int main(void)
{
	unsigned int index, digits_counts, ith_digit;
	long x;

	printf("Enter a long number and a non-negative integer:\n");
	scanf("%ld %u", &x, &index);

	// get and print the number of digits
	if (x == 0) {
		digits_counts = 0;
	} else {
		digits_counts = floor(log10(labs(x)) + 1);
	}
	printf("The number of digits in x=%ld is %d\n", x, digits_counts);

	// get the i-th digit
	if ((index == 0) || (index > digits_counts)) {
		printf("ERROR: i=%u is an invalid digit number for x=%ld\n", index, x);
		return 1;
	}
	
	ith_digit = (labs(x) % (int)pow(10, index)) / (int)pow(10, index-1);
	printf("The digit of x=%ld at index i=%d is %d\n", x, index, ith_digit);

	return 0;
}