#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
void print_letters(char argv[], int len);

void print_arguments(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		print_letters(argv[i], strlen(argv[i]));
		printf("\n");
	}
}

void print_letters(char argv[], int len)
{
	int i = 0;

	for(i = 0; i < len; i++) {
		char ch = argv[i];

		// isalpha, isblank, isdigit takes an unsigned char and tests whether it
		// falls into a certain character class 
		// the (int) before each ch, type casts the unsigned char into an int
		// remember that an ascii character is actually an int
		if (isalpha((int)ch) || isblank((int)ch)) {
			printf("'%c' == %d ", ch, ch);
		} else if (isdigit((int)ch)) {
			printf("'%c' == %d ", ch, ch);
		} else if (!isascii((int) ch)) {
			printf("not ascii: %c ", ch); // prints gibberish if the char are not ascii
		} else {
			printf("blob ");
		}
	}
}

int main(int argc, char *argv[])
{
	print_arguments(argc, argv);
	return 0;
}

