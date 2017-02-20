#include <stdio.h>

int main(int argc, char *argv[])
{
	// create two arrays
	int ages[] = { 23, 43, 12, 89, 2 };
	char *names[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	printf("Using array indexing:\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	printf("---\n");

	// setup the pointers
	int *cur_age = ages;
	char **cur_name = names;

	printf("Using pointers:\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", *(cur_name + i), *(cur_age + i));
	}
	printf("---\n");

	printf("Indexing the pointers:\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");

	// pointing cur_age an int pointer at names an array of pointers to strings
	// need to type cast
	int *bad_age = (int*)names;
	printf("Indexing bad_age pointer; an int pointer pointing at names:\n");
	printf("With type casting the pointer is pretending that names are ints.\n");
	for (i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", cur_name[i], bad_age[i]);
	}
	printf("---\n");

	// backwards
	printf("Looping the names in reverse order, with i-- idiom.\n");

	//tried this:

	//int *reverse_age = &(ages[count]);
	//char **reverse_name = &(names[count]);
	/*for (i = count; i > 0; i--) {
		printf("%s has %d years alive.\n", reverse_name[i], reverse_age[i]);
	}*/

	// but there is a common idiom
	// i = count gets the pointer to point at the last name
	// TEST tests to check if the i is decremented, would it be greater than 0
	for (i = count; i-- > 0;) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");
	
	// another way to reverse
	// make sure the index starts at the last index (usually count MINUS one)
	printf("I prefer to reverse by checking for i >= 0\n");
	for (i = count-1; i >= 0; i--) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");

	// getting the math wrong in the for loop
	printf("Getting the math wrong in the for loop.\n");
	for (i = 1; i < count; i-=2) {
		printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
	}




	return 0;
}

