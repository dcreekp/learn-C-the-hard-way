#include <stdio.h>
#include <ctype.h>

// including this other header file ctype so that I can use a string function
// tolower() or toupper()

// the main function can take any number of arguments

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("ERROR: You need at least one argument.\n");
		// this is how you abort a program
		return 1;
	}

	int i = 0;
	int j = 1;
	for (j = 1; argv[j] != '\0'; j++) {

		// making sure to loop over each argument
		// printf("%s\n", argv[j]);

		// assigning each argument to the 'word' pointer
		char *word = argv[j]; 

		// and then iterate over the word to get each letter
		for (i = 0; word[i] != '\0'; i++) {
			char letter = word[i];	

			// to lowercase function 
			letter = tolower(letter);

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
					printf("%d: '%c' is not a vowel.\n", i, letter);
			}
		}
	}
	return 0;
}

