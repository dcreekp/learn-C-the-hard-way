#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;

	if (argc == 1) {
		printf("You only have one argument. You suck.\n");
	} else if (argc > 1 && argc < 4 || argc > 5) { 
      // messing around with silly condition
	  // compiler gives a warning to parenthesise the '&&' conditionals
		printf("Here are your arguments.\n");

		for (i=0; i<argc; i++) {
			printf("%s ", argv[i]);
		}
		printf("\n");
	} else if (argc = 1) {
	  // another booby trap
	  // = is assign, so assigning anything that is not '0' will be evaluated
	  // as true
	  	printf("This prints because argc just got assigned instead of compared.\n");
	} else {
		printf("You have too many arguments. You suck.\n");
	}
}

