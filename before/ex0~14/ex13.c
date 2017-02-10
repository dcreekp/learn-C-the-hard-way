#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("ERROR: You need one argument.\n");
		// this is how you abort a program
		return 1;
	}

	int i, j;

	for (j = 1; j < argc; j++) {
		char *letters = argv[j];
		printf("arg %d\n", j);

		for (i = 0; letters[i] != '\0'; i++) {
			char letter = letters[i];

			// change letter to lowercase
			if (letter > 64 && letter < 91) {
				letter += 32;
			}

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
					if (i > 2) {
						// it's only sometimes Y
						printf("%d: 'Y'\n", i);
						break;
					} // else with the break inside the if 
					  // it goes to default and y is just a consonant
				default:
					printf("%d: %c is not a vowel\n", i, letter);
			}
		}
	}
	return 0;
}
