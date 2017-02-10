#include <stdio.h>

int main(int argc, char *argv[])
{
	// forget to initialise char name[4] = { 'a' }; this gets an error msg

	printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);
	
	printf("name: %s\n", name);
	
	// initialise numbers
	int numbers[4] = { 0 };
	
	// first print them out raw
	printf("numbers: %d %d %d %d\n",
			numbers[0], numbers[1], numbers[2], numbers[3]);
	
	// setup numbers
	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;
	
	// then print them out initialised
	printf("numbers: %d %d %d %d\n",
			numbers[0], numbers[1], numbers[2], numbers[3]);

	// initialise name with too many
	char name[4] = {'a', 'a', 'a', 'a', 'a'};
	// this gets an error msg and doesn't print the next two lines
	printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);
	printf("name: %s\n", name);

	// setup the name
	name[0] = 'Z';
	name[1] = 'e';
	name[2] = 'd';
	name[3] = 'A';  // breaking it by forgetting the special '\0' character
					// this does not get an error msg, instead prints out junk
	
	printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

	// print the name like a string
	printf("name: %s\n", name);

	//another way to use name
	char *another = "Zed";

	printf("another: %s\n", another);

	printf("another each: %c %c %c %c\n", 
			another[0], another[1], another[2], another[3]);

	return 0;	
}	

