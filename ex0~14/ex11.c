// ex11 while loop and boolean expressions
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		printf("Need at least one argument.\n");
		return 1;
	}
	// go through each string in argv
	printf("forwards\n");
	int i = 0;
	while(i < argc) {
		if (i > 2) {
			break;
		}
		printf("arg %d: %s\n", i , argv[i]);
		i++;
	}

	// let's go backwards
	printf("backwards\n");
	i = argc - 1;
	while(i >= 0) {
		printf("arg %d: %s\n", i, argv[i]);
		i--;
	}

	// let's make our own array of strings

	char *states[] = {
		"California", "Oregon", "Washington", "Texas"
	};

	int num_states = 4;
	i = 0; // watch for this
	while(i < num_states) {
		printf("state %d: %s\n", i, states[i]);
		i++;
	}

	// copy argv into states
	i = 0;
	while(i < num_states && i < argc) {
		states[i] = argv[i];
		i++;
	}
	for(i = 0; i < num_states; i++) {
		printf("argv in state %d: %s\n", i, states[i]);
	}
	for(i = 0; i < argc; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}

	// ex15 use pointers
	char **pointer_states = states;
	
	for(i = 0; i < num_states; i++) {
		printf("pointer state %d: %s\n", i, *(pointer_states + i));
	}

	return 0;
}
