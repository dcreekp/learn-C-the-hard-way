#include <stdio.h>

int main(int argc, char *argv[])
{
	int areas[] = { 10, 12, 13, 14, 20 };
	char name[] = "Zed";
	char full_name[] = {
		'Z', 'e', 'd', 
		' ', 'A', '.', ' ',
		'S', 'h', 'a', 'w', '\0'
	};

	// WARNING: on some systems you may have to change the %ld in this code to a
	// %u since it will use unsigned ints
	
	// on a 64bit cpu the byte size of an int is:
	printf("The size of an int: %ld\n", sizeof(int));

	// with five ints in makes sense that the size of areas is:
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number if ints in areas: %ld\n", 
			sizeof(areas) / sizeof(int));
	printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

	printf("The size of a char: %ld\n", sizeof(char));
	printf("The size of name (char[]): %ld\n", sizeof(name));
	printf("The number of chars in name: %ld\n", sizeof(name) / sizeof(char));

	printf("The size of full name (char[]): %ld\n", sizeof(full_name));
	printf("The number of chars in full name: %ld\n",
			sizeof(full_name) / sizeof(char));

	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	return 0;
}

			
