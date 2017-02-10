#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {
	struct Address rows[MAX_ROWS];
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}





int main(int argc, char *argv[])
{
	printf("testing\n");
	
	struct Address *addr = {.id = 1, .set = 0, .name = "tarbo",
							.email = "dcreekp@gmail.com"
	};

	Address_print(addr);

	return 0;
}
