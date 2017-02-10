// ex16 initialising a struct on the heap
#include <stdio.h>    // includes standard input output functions
#include <assert.h>   // includes assert functions
#include <stdlib.h>   // includes things like malloc
#include <string.h>   // includes string related functions

struct Person {
// basically creating a structure named Person to hold data of this kind:
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
// a function named Person_create that returns an "instance" of Person struct
{
	struct Person *who = malloc(sizeof(struct Person));
	// malloc is for allocating the right size of memory to a pointer

	assert(who != NULL); // check that who exists in memory
	
	// assign each element of who to the argument values
	who->name = name; //strdup(name); 
	// strdup is from string.h, it returns a pointer to a new string which
	// becomes a duplicate of the string passed in as the argument
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
// a function that destroys the given "instance" of the Person Struct
{
	assert(who != NULL);  // checks that who still exists in memory

	//free(who->name);    // releases the allocated memory
	free(who);			// so that it is no longer allocated
}

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
	struct Person *joe = Person_create(
			"Joe Alex", 32, 64, 140);
	struct Person *frank = Person_create(
			"Frank Blank", 20, 72, 180);

	// print them out and where they are in memory
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);
	
	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);
	
	// make everyone age 20 years and print them again
	printf("Let's age them by twenty years.\n");

	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);
	
	frank->age += 20;
	frank->weight += 20;
	Person_print(frank);
	
	//destroy them both so we can clean up
	Person_destroy(joe);
	Person_destroy(frank);
	
	return 0;
}

