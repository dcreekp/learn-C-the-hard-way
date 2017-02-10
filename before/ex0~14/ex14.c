#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		print_letters(argv[i]);
	}
}

void print_letters(char arg[])
{
	int i = 0;

	for(i = 0; arg[i] != '\0'; i++) {
		char ch = arg[i];

		if (can_print_it(ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}
	printf("\n");
}

int can_print_it(char ch)
{
	return isalpha(ch) || isblank(ch);
}

/* ///////////////////////////////////
 * reworking the functions
 */

void reprint_letters(char arg[], int arg_len);

void reprint_arguments(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		char *arg = argv[i];
		int arg_len = strlen(arg); // using a function from string.h
		reprint_letters(arg, arg_len);
	}
}

void reprint_letters(char arg[], int arg_len)
{
	int i = 0;

	for (i = 0; i < arg_len; i++) {
		char ch = arg[i];

		if (isalpha(ch) || isblank(ch)) {
			printf("'%c' == %d ", ch, ch);
		} 
		else if (isdigit(ch)) {
			printf("number %c == %d ", ch, ch);
		}
		else if (ispunct(ch)) {
			printf("punctuation %c == %d ", ch, ch);
		}
		else {
			printf("what else? %c == %d ", ch, ch);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("ERROR: need an argument.\n");
		return 1;
	}
	print_arguments(argc, argv);
	reprint_arguments(argc, argv);
	return 0;
}
