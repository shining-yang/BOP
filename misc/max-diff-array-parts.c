/*
 * Given an array, say a[N], and an index, say K.
 * DIFF = abs(max{a[0], ..., a[k]} - max{a[k+1], ..., a[N-1]})
 * Write a program to output the MAX DIFF within O(N) complexity
 */

/*
 * Trying to take the absolute value of the most negative integer is not defined.
 */

/*
 * Consider data overflow ?
 */

#include <stdio.h>
#include <stdlib.h>

int max_diff(int a[], int n)
{
	int i,  m = a[0];
	for (i = 0; i < n; i++) {
		if (m < a[i]) {
			m = a[i];
		}
	}

	int l = abs(m - a[0]);
	int r = abs(m - a[n - 1]);
	return l > r ? l : r;
}

int main(int argc, char** argv)
{
	int A[] = { 2, -1, 3, 5, 1, -6, 3, 2, -7, 8, 1, -2 };
	int m = max_diff(A, sizeof(A) / sizeof(A[0]));
	printf("Max is: %d\n", m);
	return 0;
}
