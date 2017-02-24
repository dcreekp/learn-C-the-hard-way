#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// setting up an array of pointers to struct Person
// for loop to call the functions on each Person

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
	assert(who != NULL);
	free(who->name);
	free(who);
}

// printing the memory location of the elements
// name is already a pointer so no need for &
// but the rest a values so need th & to "get address of"
void Person_print(struct Person *who)
{
	printf("Name: %s, memory location: %p\n", who->name, who->name);
	printf("\tAge: %d, memory location: %p\n", who->age, &(who->age));
	printf("\tHeight: %d, memory location: %p\n", who->height, &(who->height));
	printf("\tWeight: %d, memory location: %p\n", who->weight, &(who->weight));
}

int main(int argc, char *argv[])
{
	// two people structures
	struct Person *joe = Person_create("Joe Alex", 32, 63, 140);
	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	// create an array of pointers to struct Person
	struct Person *people[] = { joe, frank };

	int i = 0;
	int count = sizeof(people) / sizeof(people[0]);

	for (i = 0; i < count; i++) {
		printf("This struct Person with memory location %p is:\n", people[i]);
		Person_print(people[i]);
		printf("---\n");
	}

	// make everyone age 20 years
	for (i = 0; i < count; i++) {
		people[i]->age += 20;
	}
	joe->height -= 2;
	joe->weight += 40;
	frank->weight += 20;

	for (i = 0; i < count; i++) {
		printf("This struct Person with memory location %p is:\n", people[i]);
		Person_print(people[i]);
		printf("---\n");
	}

	for (i = 0; i < count; i++) {
		Person_destroy(people[i]);
	}

	return 0;
}

