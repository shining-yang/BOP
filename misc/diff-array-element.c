#include <stdio.h>
#include <stdlib.h>

/*
 * Give an array of integers, every element appears 3 times except for one.
 * Find that one.
 */
int find_except(int a[], int n)
{
	int one = 0, acc = 0;
	int i, t;

	for (i = 0; i < n; i++) {
		acc |= a[i] & one;
		one ^= a[i];

		t = one & acc;
		one &= ~t;
		acc &= ~t;
	}

	return one;
}

int main(int argc, char** argv)
{
	int a[] = { -1, -2, -1, -1 };
	int ex = find_except(a, sizeof(a) / sizeof(a[0]));
	printf("Exception: %d\n", ex);

	int b[] = { 1, 1, -2, 3, 5, 1, -2, 3, -2, 3 };
	int ex2 = find_except(b, sizeof(b) / sizeof(b[0]));
	printf("Exception: %d\n", ex2);
	return 0;
}
