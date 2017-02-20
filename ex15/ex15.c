#include <stdio.h>

int main(int argc, char *argv[])
{
	// strings can be expressed as pointers or arrays
	char *name = "Tarbo";
	char rename[] = "Obrat";

	printf("string as pointer name: \"%s\"\n", name);
	printf("string as array rename: \"%s\"\n", rename);

	// the size of a pointer is 8 bytes regardless of what it is pointing to
	// the size of an array depends on number of elements before the null
	printf("size of pointer name: %ld, size of array rename: %ld\n", 
			sizeof(name), sizeof(rename));

	// the size of a character, what *name is pointing to (or the value of name)
	// and what rename[0] is indexing to, is obviously the same
	printf("size of *name and rename[0]: %ld, %ld\n", 
			sizeof(*name), sizeof(rename[0])); 

	// getting the address of name
	printf("The pointer: name, as in the memory block, is indexed at %p\n",
			name);
	printf("The size of which is %ld\n", sizeof(name));

	// create two arrays
	int ages[] = { 23, 43, 12, 89, 2 };
	char *names[] = {
		"Alan", "Frank", 
		"Mary", "John", "Lisa"
	};

	printf("Since a pointer takes 8 bytes and there are five pointers in the names array\n");
	printf("The size of names: %ld\n", sizeof(names)); 
	printf("---\n");

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	// first way using indexing
	printf("Using array indexing.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");

	// setup the pointers to the start of the arrays
	int *cur_age = ages;
	char **cur_name = names;

	// second way using pointers
	printf("Using pointers.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", *(cur_name + i), *(cur_age + i));
	}
	printf("---\n");

	// how about just getting the pointer address
	printf("The pointers' address:\n");
	for ( i = 0; i < count; i++) {
		printf("cur_name: %d, cur_age: %d.\n", (cur_name + i), cur_age + i);
	}
	printf("---\n");

	// the wrong way: gets the value of cur_name and then adds the i
	printf("The wrong way: getting the value of cur_age and then adding i.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", *cur_name + i, *cur_age + i);
	}
	printf("---\n");

	// third way using pointers like arrays
	printf("The best way, indexing the pointers.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");
		
	// another one to print the addresses of the pointers
	printf("Printing the addresses.\n");
	for (i = 0; i < count; i++) {
		printf("%s which is indexed at, %p, has %d years alive.\n", 
				cur_name[i], cur_name[i], cur_age[i]);
	}
	printf("---\n");

	// fourth way with pointers in a stupid complex way
	printf("Using pointers in a complex way.\n");
	for (cur_name = names, cur_age = ages;
			(cur_age - ages) < count; cur_name++, cur_age++) {
		printf("%s has %d years alive.\n", *cur_name, *cur_age);
	}
	printf("---\n");
	
	// the fourth way is annoying because in order to re-iterate through the 
	// names again, need to reset the pointer
	printf("One last time.\n");
	cur_name = names;
	cur_age = ages;
	for (i = 0; i < count; i++ ) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
	}

	return 0;
}


