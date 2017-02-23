#include <stdio.h>

// all arrays as pointers 


int main (int argc, char *argv[])
{
	// two "arrays"
	int ages[] = { 23, 43, 12, 89, 2 };
	int (*a)[] = &ages;
	/*char (**names)[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};*/

	// safely get the size of ages
	int count = sizeof(a);
	int i = 0;
	printf("%d\n", count);

	printf("Using array indexing.\n");
	for (i = 0; i < count; i++) {
		printf("%d years alive.\n", *(a + i));
	}






	return 0;
}

// using this:
// http://stackoverflow.com/questions/17850998/initializing-a-pointer-to-an-array-of-integers
