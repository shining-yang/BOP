/*
 * Words with same letters but different order. E.g. stop and spot
 */
#include <stdio.h>

/*
 * for C language
 */
#define bool	int
#define true	1
#define false	0

/*
 * Determine if two strings are anagram
 * Complexity: O(n)
 */
 bool anagram(unsigned char* s1, unsigned char* s2)
 {
	int i;
 	long counter[256 / sizeof(long)] = { 0 };
 	char* buf = (char*)&counter;

	while (*s1 && *s2) {
		buf[*s1++]++;
		buf[*s2++]--;
	}

	if (*s1 || *s2) {
		return false;
	}

	for (i = 0; i < sizeof(counter) / sizeof(counter[0]); i++) {
		if (counter[i] != 0) {
			return false;
		}
	}

	return true;
 }

int main(int argc, char** argv)
{
	char* s1 = "stop";
	char* s2 = "spot";
	puts(anagram(s1, s2) ? "Yes" : "No");

	char* s3 = "abcd";
	char* s4 = "bcae";
	puts(anagram(s3, s4) ? "Yes" : "No");

	return 0;
}
