#include <stdio.h>
#include <ctype.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
	// prints the arguments that main typically gets
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		print_letters(argv[i]);
	}
}

void print_letters(char argv[])
	// gets called by print_arguments, knows how to print each of the characters
{
	int i = 0;
	
	for (i = 0; argv[i] != '\0'; i++) {
		char ch = argv[i];

		if (can_print_it(ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}
	printf("\n");
}

int can_print_it(char ch)
	// isalpha and isblank comes from ctype.h
	// returns the truth value 0 or 1
{
	return isalpha((int)ch) || isblank((int)ch);
}

int main(int argc, char *argv[])
	// just calls print_arguments to start the chain of functions
{
	print_arguments(argc, argv);
	return 0;
}

