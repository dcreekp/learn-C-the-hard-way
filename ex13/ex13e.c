#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	char *states[] = { 
		"California", "Oregon", "Washington", "Texas"
	};

	// assigning a state to the argv array before printing either
	argv[1] = states[0];

	for (i = 1; i < argc; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}

	int number_states = 4;
	i = 0;
	
	// assigning an argv element to states
	states[3] = argv[2];

	// doesn't necessarily need to initialize in the parenthesises
	printf("No need to initialise inside the for parenthesises.\n");
	for (; i < number_states; i++) {
		printf("state %d: %s\n", i, states[i]);
	}
	// but now the i = 4, so need to reintialise
	printf("More states.\n");
	for (i = 0; i < number_states; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	int j = 0;
	// using a comma operator in the TEST
	// j takes the value of i, that result is used to check whether j is less
	// than number_states
	printf("Using comma operator.\n");
	for (i = 0; j = i, j < number_states; i++) {
		printf("state %d: %s\n", i, states[j]);
	}

	// how does a NULL print
	printf("How a does a NULL print?\n");
	states[1] = NULL;
	for (i = 0; i < number_states; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	// here is a good way to use the NULL 
	printf("A way to use NULL is to put it at the end of an array, so the TEST can be states[i] != NULL\n");
	states[1] = "Oregon";
	states[4] = NULL;
	for (i = 0; states[i] != NULL; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	// what exactly is argv
	printf("Actually argv has the shell's environment variables in it's array\n");
	for(i = 0; i < 8; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}

	// using sizeof for the length of an array
	number_states = sizeof(states) / sizeof(states[0]);
	printf("The number of elements in states: %d\n", number_states);
	for (i = 0; i < number_states; i++) {
		printf("states %d: %s\n", i, states[i]);
	}


	return 0;
}

