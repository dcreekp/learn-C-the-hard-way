#include <stdio.h>
#include <ctype.h>

// forward declarations
// commenting out these forward to declarations
// int can_print_it(char ch);
// void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		print_letters(argv[i]);
	}
}

void print_letters(char argv[])
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
{
	return isalpha((int)ch) || isblank((int)ch);
}

int main(int argc, char *argv[])
{
	// incrementing argc causes a segementation fault
	argc++ ;
	printf("incremented argc to: %d.\n", argc);
	print_arguments(argc, argv);
	return 0;
}

