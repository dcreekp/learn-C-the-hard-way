#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// creating a structure that has four elements
struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

// a function to create a pointer to struct Person
// need to declare the type that the function is going to return: a struct
// Person pointer
// and then declare the parameters that it needs
struct Person *Person_create(char *name, int age, int height, int weight)
{
	// this bit allocates memory space to the pointer
	// it allocates precisely the amount needed for the type: struct Person
	struct Person *who = malloc(sizeof(struct Person));

	// making sure that there is memory space for *who
	assert(who != NULL);
	
	// strdup: allocates and duplicates a string (needed because name is a 
	// pointer, it gets the value of the pointer and allocates the value another
	// separate memory space)
	who->name = strdup(name);	
	(*who).age = age;           // same as who->age = age;
	who->height = height;		// get the value of who (a struct) and creates
	who->weight = weight;	    // a reference 
								// remember -> means struct dereference	
	return who;
}

// a function to free the memory space that was allocated to the pointer
// pointing to a struct Person
void Person_destroy(struct Person *who)
{
	// checking that who exists because freeing an empty will cause a segfault
	assert(who != NULL); 
	free(who->name);
	free(who);
}

// a function which takes a pointer to a struct Person and prints out the
// struct's attributes
void Person_print(struct Person *who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
	// make two people structures
	struct Person *joe = Person_create("Joe Alex", 32, 64, 140);

	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	// print them out and where they are in memory
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);
	
	// make everyone age 20 years and print them again
	printf("Let's age everyone by twenty years:\n");

	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	Person_print(frank);

	// destroy them both so we clean up
	Person_destroy(joe);
	Person_destroy(frank);

	return 0;
}

