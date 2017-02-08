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

		// each character is actually to an integer 
		// the integer maps to an ASCII to letter
		// printf("%d\n", letter);
		// printf("%c\n", letter);

		// A = 65, Z = 90, any Uppercase letter gets added by 32
		if (65 <= letter && letter <= 90) {
			letter += 32;
		}
		// to be changed into a Lowercase letter
		// printf("%c\n", letter);

		// means no need to specify case A or the other Uppercase vowels
		switch (letter) {
			case 'a':
				printf("%d: 'A'\n", i);
				break;
			case 'e':
				printf("%d: 'E'\n", i);
				break;
			case 'i':
				printf("%d: 'I'\n", i);
				break;
			case 'o':
				printf("%d: 'O'\n", i);
				break;
			case 'u':
				printf("%d: 'U'\n", i);
				break;
			case 'y':
				// why i > 2? is this a bug?
				if (i > 2) {
					// it's only sometimes Y
					printf("%d: 'Y'\n", i);
				}
				break;
			default:
				printf("%d: %c is not a vowel.\n", i, letter);
		}
	}

	return 0;
}

