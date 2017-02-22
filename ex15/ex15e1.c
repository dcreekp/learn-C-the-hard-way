#include <stdio.h>

int main(int argc, char *argv[])
{
	// two arrays
	int ages[] = { 23, 43, 12, 89, 2 };
	char names[][] = {
		{'A', 'l', 'a', 'n', '\0'},
		{'F', 'r', 'a', 'n', 'k', '\0'},
		{'M', 'a', 'r', 'y', '\0'},
		{'J', 'o', 'h', 'n', '\0'},
		{'L', 'i', 's', 'a', '\0'}
	};

	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	for (i = 0; i < count; i++) {
		printf("%d years alive.\n", ages[i]);
	}

	return 0;
}

