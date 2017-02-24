#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// breaking it

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);

	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
{
	// what happens if a NULL pointer is passed in and the assert is commented
	// out
	//assert(who != NULL);
	
	// what happens if who->name is not freed
	free(who->name);
	free(who);
}

void Person_print(struct Person *who)
{
	printf("Name: %s in memory location %p\n", who->name, who->name);
	printf("\tAge: %d in memory location %p\n", who->age, &(who->age));
	printf("\tHeight: %d in memory location %p\n", who->height, &(who->height));
	printf("\tWeight: %d in memory location %p\n", who->weight, &(who->weight));
}

int main(int argc, char *argv[])
{
	// create two struct Persons
	struct Person *joe = Person_create("Joe Alex", 32, 63, 140);
	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	// print them out
	printf("Joe is at memory location %p\n", joe);
	Person_print(joe);
	printf("Frank is at memory location %p\n", frank);
	Person_print(frank);
	// passing in NULL instead of frank screws everything up
	// alot of memory will not be freed as well

	// age them by 20 years
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	frank->age += 20;
	frank->weight += 20;

	printf("Joe is at memory location %p\n", joe);
	Person_print(joe);
	printf("Frank is at memory location %p\n", frank);
	Person_print(frank);

	// what happens if you forget to free the memory
	Person_destroy(NULL);
	Person_destroy(frank);

	return 0;
}
