#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

// struct with arrays for string
struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

// a struct of a an array of structs
struct Database {
	struct Address rows[MAX_ROWS];
};

// another struct which has a struct
struct Connection {
	FILE *file;
	struct Database *db;
};

// check that struct will work
int main (int argc, char *argv[])
{
	struct Address *addr = malloc(sizeof(struct Address));

	addr->id = 10;
	addr->set = 1;
	// this addr->name[20] = "Tarbo";
	// gives this warning
	// ex17.c:37:17: warning: assignment makes integer from pointer without a cast [-Wint-conversion]
	// so use this function
	strncpy(addr->name, "Tarbo", MAX_DATA);
	strncpy(addr->email, "f.tarbo@gmail.com", MAX_DATA);

	printf("addr at %p contains:\n", addr);
	printf("id: %d\n", addr->id);
	printf("set: %d\n", addr->set);
	printf("name: %s\n", addr->name);
	printf("email: %s\n", addr->email);

	free(addr);
	return 0;
}

