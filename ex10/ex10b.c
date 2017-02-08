#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("ERROR: You need one argument.\n");
		// this is how you abort a program
		return 1;
	}

	int i = 0;
	for (i = 0; argv[1][i] != '\0'; i++) {
		char letter = argv[1][i];
		int j = i;
		switch (j) {
			case 'a':
			case 'A':
				printf("%d: 'A'\n", i);
				break;
			case 'e':
			case 'E':
				printf("%d: 'E'\n", i);
				// forgetting the break causes "fall through" into case i
			case 'i':
			case 'I':
				printf("%d: 'I'\n", i);
				break;
			case 'o':
			case 'O':
				printf("%d: 'O'\n", i);
				break;
			case 'u':
			case 'U':
				printf("%d: 'U'\n", i);
				break;
			case 'y':
			case 'Y':
				// why i > 2? is this a bug?
				if (i > 2) {
					// it's only sometimes Y
					printf("%d: 'Y'\n", i);
				}
				break;
			// not having a default leads to a silent error, not doing anything
			// when none of the cases are hit
			default:
				printf("%d: %c is not a vowel.\n", i, j);
		}
	}

	return 0;
}

