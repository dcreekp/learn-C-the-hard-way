#include <stdio.h>

int main(int argc, char *argv[])
{
	// create two arrays we care about
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = {
		"Alan", "Frank", "Mary", "John", "Lisa"};

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	// first way using indexing
	printf("indexing\n");
	for(i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");

	// setup the pointers to the start of the arrays
	int *cur_age = ages;
	// creating a pointer at ages, a pointer to integer type
	char **cur_name = names;
	// creating a pointer at names, a pointer to (a pointer to char) type

	// second way using pointers
	printf("using pointers\n");
	for(i = 0; i < count; i++) {
		printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
	}
	printf("---\n");

	// third way, pointers are just arrays
	printf("pointers as arrays\n");
	for(i = 0; i < count; i++) {
		printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");

	// fourth way with pointers in a stupid complex way
	printf("using pointers in an unnecessary way\n");
	for(cur_name = names, cur_age = ages;
			(cur_age - ages) < count;
			cur_name++, cur_age++)
	{
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}
	printf("---\n");

	/* /////////////////////////////////
	 * extra: casting
	 */
	// cur_age points to an int of names rather than a char of names so that the
	// pointer will be pointing at names but will think it is an int
	char *more_names[] = {
		"Alan", "Frank", "Mary", "John", "Lisa"};
	int *more_age = (int*)more_names;
	char **more_name = more_names;

	printf("casting, breaks the code\n");
	for(i = 0; i < count; i++) {
		printf("%s lived %d years so far.\n",
				*(more_name + i), *(more_age + i));
	}
	printf("---\n");

	/* /////////////////////////////
	 * extra: reversing the loops it breaks for the middle two
	 */
	printf("in reverse; breaks the code for some\n");
	for(i = count - 1; i >= 0; i--) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");
	for(i = count; i > 0; i--) {
		printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
	}
	printf("---\n");
	for(i = count; i > 0; i--) {
		printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");
	for(cur_name = names + count - 1, cur_age = ages + count - 1;
			(cur_age - ages) >= 0;
			cur_name--, cur_age--)
	{
		printf("%s lived %d years so far. \n",
			*cur_name, *cur_age);
	}
	printf("---\n");

	// extra: all pointers
	int *pointer_age = ages;
	char **pointer_name = names;

	printf("more pointers\n");
	for (i = 0; i < count; i++) {
		printf("%s is %d years old.\n", *(pointer_name+i), *(pointer_age+i));
	}
	printf("---\n");
	
	// extra: command line arguments with pointers and their address
	if (argc > 1) {
		char **args = argv;
		printf("pointers for command line arguments\n");
		for (i = 0; i < argc; i++) {
			printf("arg %d: %s, is at %p which is the same as %p\n", 
					i, *(args + i), &argv[i], &*(args +i));
		}
	}
	else {
		printf("no args to print.\n");
	}
	printf("---\n");
	
	// extra: the addresses of what the pointers are pointing at
	// for some reason the cur_name is pointer has shifted so that cur_name[0]
	// points at somewhere else and cur_name[1] is what you would expect of
	// cur_name[0]. It happens due to the 4th loop "using pointers in an
	// unnecessary way".
	printf("address of pointers\n");
	int j = 1;
	
	for (i = 0, j = 1; i < count; i++, j++) {
		printf("cur_name %s %p == pointer_name %s %p\n",
				*(cur_name + j), &*(cur_name + j),
				*(pointer_name + i), &*(pointer_name + i));
		printf("cur_age %d %p == pointer_age %d %p\n",
				*(cur_age + j), &*(cur_age + j),
				*(pointer_age + i), &*(pointer_age + i));
	}
		

	return 0;
}
