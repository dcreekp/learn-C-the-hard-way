#include <stdio.h>

// rewrite to use a function for each print out 
// passing pointers to these functions

// forward declarations of functions
void print_using_pointers(int count, int *ages, char **names);
void print_pointers_like_arrays(int count, int *ages, char **names);
void print_pointers_complex(int count, int *ages, char **names);
void print_passing_arrays_in_as_pointers(int count, int *ages, char **names);

void print_from_arrays(int count, int ages[], char *names[])
{
	int i = 0;
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");
}

void print_using_pointers(int count, int *ages, char **names)
{
	int i = 0;
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", *(names + i), *(ages + i));
	}
	printf("---\n");
}

void print_pointers_like_arrays(int count, int *ages, char **names)
{
	int i = 0;
	for (i = count - 1; i >= 0; i--) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");
}

void print_pointers_complex(int count, int *ages, char **names)
{
	int *cur_age = ages;
	char **cur_name = names;
	for (cur_name = names, cur_age = ages;
			cur_age - ages < count; cur_name++, cur_age++) {
		printf("%s has %d years alive.\n", *cur_name, *cur_age);
	}
	printf("---\n");
}

void print_passing_arrays_in_as_pointers(int count, int *ages, char **names)
// this works because arrays passed into functions are always converted into
// pointers
{
	int i = 0;
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");
}

int main(int argc, char *argv[])
{
	// two arrays
	int ages[] = { 23, 43, 12, 89, 2 };
	char *names[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};

	// the size
	int count = sizeof(ages) / sizeof(int);
	
	print_from_arrays(count, ages, names);

	// setup the pointers
	int *cur_age = ages;
	char **cur_name = names;

	print_using_pointers(count, cur_age, cur_name);
	print_pointers_like_arrays(count, cur_age, cur_name);
	print_pointers_complex(count, cur_age, cur_name);
	print_passing_arrays_in_as_pointers(count, ages, names);

	return 0;
}
