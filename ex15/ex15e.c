#include <stdio.h>

// all arrays as pointers 


int main (int argc, char *argv[])
{
	// two "arrays"
	int ages[5] = { 23, 43, 12, 89, 2 };
	int (*p_ages)[] = &ages;
	char *names[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};
	char (**p_names)[] = &names;

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	printf("Using indexing.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", (**p_names)[i], (*p_ages)[i]);
	}
	printf("---\n");

	int *cur_age = ages;
	char **cur_name = names;

	printf("Using pointers.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", *(cur_name + i), *(cur_age + i));
	}
	printf("---\n");

	printf("Pointers are just arrays.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");

	printf("Complex way with pointers.\n");
	for (cur_name = names, cur_age = ages;
			(cur_age - ages) < count; cur_name++, cur_age++){
		printf("%s has %d years alive.\n", *cur_name, *cur_age);
	}


	// try this
	int x[5] = {1, 2, 3, 4, 5};

	int (*a)[5] = &x;

	printf("pointer to %p\n", (a)[3]);
	printf("with value of %d\n", (*a)[3]);

	return 0;
}

// using this:
// http://stackoverflow.com/questions/17850998/initializing-a-pointer-to-an-array-of-integers
