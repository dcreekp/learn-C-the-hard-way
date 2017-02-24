#include <stdio.h>
#include <assert.h>
#include <string.h>

// the same program without using malloc
// instantiating the struct on the stack

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
	struct Person who;

	who.name = strdup(name);
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}

// passing a struct into a function
// straight forward but costly for memory
void Person_print(struct Person who)
{
	printf("Name: %s, memory location: %p\n", who.name, who.name);
	printf("\tAge: %d, memory location: %p\n", who.age, &(who.age));
	printf("\tHeight: %d, memory location: %p\n", who.height, &(who.height));
	printf("\tWeight: %d, memory location: %p\n", who.weight, &(who.weight));
}

int main (int argc, char *argv[])
{
	// create two struct Persons
	struct Person joe = Person_create("Joe Alex", 32, 63, 140);
	struct Person frank = Person_create("Frank Blank", 20, 72, 180);

	struct Person people[] = { joe, frank };

	int i = 0;
	int count = sizeof(people) / sizeof(people[0]);

	for (i = 0; i < count; i++) {
		printf("This struct Person with memory location %p is:\n", &(people[i]));
		Person_print(people[i]);
		printf("---\n");
	}
	
	return 0;
}

