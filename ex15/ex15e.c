#include <stdio.h>

// all arrays as pointers 

int main (int argc, char *argv[])
{
	// two "arrays"
	int (*ages)[8] = { 23, 43, 12, 89, 2 };
	char (**names)[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};

	// safely get the size of ages
	int count = sizeof(ages);
	int i = 0;
	printf("%d\n", count);

	printf("Using array indexing.\n");
	for (i = 0; i < count; i++) {
		printf("%d years alive.\n", ages[i]);
	}






	return 0;
}
