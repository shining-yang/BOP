/*
 * Equilibrium Index
 *
 * Given an array, find any equilibrium index that make the sum of LEFT-PART equals RIGHT PART
 *
 * Valid index range: [0, N)
 *
 * IF index is 0, then the LEFT-PART sum is 0. ALSO, if index is N-1, then the RIGHT-PART sum is 0
 */
#include <stdlib.h>
#include <stdio.h>

int equi_index(int a[], int n)
{
	int i;
	double left = 0, right = 0;

	for (i = 0; i < n; i++) {
		right += a[i];
	}

	for (i = 0; i < n; i++) {
		right -= a[i];
		if (i > 0) {
			left += a[i - 1];
		}

		if (left == right) {
			return i;
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	int A[] = { -1, 3, -4, 5, 1, -6, 2, 1 };
	int index = equi_index(A, sizeof(A) / sizeof(A[0]));
	printf("Index is: %d\n", index);
	return 0;
}

