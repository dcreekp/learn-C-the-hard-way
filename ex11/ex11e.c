#include <stdio.h>

int main(int argc, char *argv[])
{
	// assigning charactes into an array of ints
	int numbers[4] = { 'a', 'b', 'c', 'd'};
	// this will just produce the bytecode of the letters
	// basically be like this {97 98 99 100}
	printf("numbers: %d %d %d %d\n",
			numbers[0], numbers[1], numbers[2], numbers[3]);

	// changing it form
	char name[4] = { 'a' }; 
	// to 
	// char *name = { 'a' };   
	// will segfault at runtime

	printf("name: %s\n", name);
	printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

	// setup numbers
	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;

	printf("numbers: %d %d %d %d\n",
			numbers[0], numbers[1], numbers[2], numbers[3]);

	// setup the name
	name[0] = 'Z';
	name[1] = 'e';
	name[2] = 'd';
	name[3] = '\0';
	
	printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

	printf("name: %s\n", name);

	//another way to use name
	char *another = "Zed";

	printf("another: %s\n", another);

	printf("another each: %c %c %c %c\n", 
			another[0], another[1], another[2], another[3]);

	// treating the name as an array of ints
	int i = 0;
	for (i = 0; i < 4; i++) {
		printf("%d\n", another[i]); // printing each character as an int
									// produces the bytecode of the character
	}

	// treat the name array like a 4 byte integer
	printf("four byte integer? %d\n", name);

	return 0;	
}	

