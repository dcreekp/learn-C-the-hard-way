#include <stdio.h>

int main (int argc, char *argv[])
{
	int areas[] = { 10, 12, 13, 14, 20 };
	char name[] = "Zed";
	char full_name[] = {
		'Z', 'e', 'd',
		' ', 'A', '.', ' ',
		'S', 'h', 'a', 'w', '\0'
	};

	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number of ints in areas: %ld\n",
			sizeof(areas) / sizeof(int));
	printf("The first area is %d, the 2nd is %d.\n", areas[0], areas[1]);

	// assigning new values in an array
	areas[0] = 100;
	areas[4] = 500;
	areas[100] = 3;
	printf("The new first area is %d, and the last is %d and anything between index 4 and 100 is %d.\n",
			areas[0], areas[100], areas[50]);

	printf("The size of char: %ld\n", sizeof(char));
	printf("The size of name: %ld\n", sizeof(name));
	printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

	name[2] = "TED"; 
	// compiler gives a warning, each index can hold only one char
	printf("Name with mistake%s \n", name);

	// assigning to elements of name
	name[0] = 'T';
	name[1] = 'a';
	name[2] = 'r';
	name[3] = 'b';
	name[4] = 'o';
	name[5] = '\0';

	printf("The new name is: %s\n", name);

	printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
	printf("The number of chars: %ld\n",
			sizeof(full_name) / sizeof(char));

	// assigning elements to full_name
	full_name[14] = 'H';
	// assigning an element of areas into full_name
	full_name[10] = areas[0];

	printf("Full_name with an areas element: %s\n", full_name);

	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	// printing a nul byte at full_name[13] will show nothing
	printf("Assigned full_name[14]: %c, and what is in between at full_name[13]: %c\n",
			full_name[14], full_name[13]);

	return 0;
}
