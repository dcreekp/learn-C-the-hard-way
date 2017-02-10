#include <stdio.h>

void indexing(int count, char *names[], int ages[])
// first way using indexing
{
	printf("indexing\n");
	for(int i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");

	printf("while indexing\n");
	int i = 0;
	while(i < count) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
		i++;
	}
	printf("---\n");
}

void pointers(int count, char **names, int *ages)
// second way using pointers 
{
	printf("using pointers\n");
	for(int i = 0; i < count; i++) {
		printf("%s is %d years old.\n", *(names + i), *(ages + i));
	}
	printf("---\n");

	printf("using pointers and while loop\n");
	int i = 0;
	while(i < count) {
		printf("%s is %d years old.\n", *(names +i), *(ages + i));
		i++;
	}
	printf("---\n");
}

void pointers_as_arrays(int count, char **names, int *ages)
// third way using pointers as arrays
// probably the best way
{
	printf("pointers as arrays\n");
	for(int i = 0; i < count; i++) {
		printf("%s is %d years old again.\n", names[i], ages[i]);
	}
	printf("---\n");

	printf("pointers as arrays in while loop\n");
	int i = 0;
	while(i < count) {
		printf("%s is %d years old again.\n", names[i], ages[i]);
		i++;
	}
	printf("---\n");
}

void pointers_stupid_way(int count, char *names[], int ages[])
// fourth way with pointers in a stupid complex way
{
	printf("using pointers in an unnecessary way\n");
	char **un_name = names;
	int *un_age = ages;

	for(un_name = names, un_age = ages;
			(un_age - ages) < count;
			un_name++, un_age++)
	{
		printf("%s lived %d so far.\n", *un_name, *un_age);
	}
	printf("---\n");
	
	printf("using pointers in an unnecessary way in a while loop\n");
	un_name = names, un_age = ages;
	while((un_age - ages) < count) {
		printf("%s lived %d so far.\n", *un_name, *un_age);
		un_name++, un_age++;
	}
	printf("---\n");
}

void command_line_args(int argc, char **args)
// command line arguments and their address
{
	printf("pointers for command line arguments\n");
	for(int i = 0; i < argc; i++) {
		printf("arg %d: %s is at %p, same as %p.\n",
				i, args[i], &args[i], &*(args + i));
	}
	printf("---\n");
}

void two_pointers(int count, char **cur_name, int *cur_age, 
		char **pointer_name, int *pointer_age)
// comparing two pointers
{
	printf("two pointers point to the same address\n");
	for(int i = 0; i < count; i++) {
		printf("cur_name %s address %p == pointer_name %s address %p\n",
				cur_name[i], &cur_name[i], pointer_name[i], &pointer_name[i]);
		printf("cur_age %d address %p == pointer_age %d address %p\n",
				cur_age[i], &cur_age[i], pointer_age[i], &pointer_age[i]);
	}
	printf("---\n");
}

int main(int argc, char *argv[])
{
	// create two arrays we care about
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = {
		"Alan", "Frank", "Mary", "John", "Lisa"};

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);

	// first way using indexing
	indexing(count, names, ages);

	// setup the pointers to the start of the arrays
	// creating a pointer at ages, a pointer to integer type
	int *cur_age = ages;
	// creating a pointer at names, a pointer to (a pointer to char) type
	char **cur_name = names;

	// second way using pointers
	pointers(count, cur_name, cur_age);

	// third way, using pointers as arrays
	pointers_as_arrays(count, cur_name, cur_age);

	// fourth way with pointers in a stupid complex way
	pointers_stupid_way(count, names, ages);

	// command line arguments and their address
	if (argc > 1) {
		char **args = argv;
		command_line_args(argc, args);
	}
	else {
		printf("no args to print.\n");
	}
		
	// new pointers
	int *pointer_age = ages;
	char **pointer_name = names;

	two_pointers(count, cur_name, cur_age, pointer_name, pointer_age);

	return 0;
}
