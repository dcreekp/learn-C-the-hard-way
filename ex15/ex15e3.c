#include <stdio.h>

// writing the for loops as while loops

int main(int argc, char *argv[])
{	
	// two arrays
	int ages[] = { 23, 43, 12, 89, 2 };
	char *names[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};

	// get the size
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	// first way using indexing
	while (i < count) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
		i++;
	}
	printf("---\n");

	// setting up pointers
	int *cur_age = ages;
	char **cur_name = names;

	// using pointers
	i = 0;
	while (i < count) {
		printf("%s has %d years alive.\n", *(cur_name + i), *(cur_age + i));
		i++;
	}
	printf("---\n");

	// using pointers as arrays
	i = 0;
	while (i < count) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
		i++;
	}
	printf("---\n");

	// backwards
	i = count - 1;
	while (i >= 0) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
		i--;
	}
	printf("---\n");

	// the confusing way
	cur_name = names;
	cur_age = ages;
	while ((cur_age - ages) < count) {
		printf("%s has %d years alive.\n", *cur_name, *cur_age);
		cur_name++, cur_age++;
	}
	printf("---\n");

	return 0;
}

