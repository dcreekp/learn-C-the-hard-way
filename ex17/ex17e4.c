#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

/*
   rework the program to use a single global for the database connection.
   (not usually a good idea)
*/

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

// declaring a global pointer named conn which is initialised empty
struct Connection *conn = NULL;

void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s \n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die("Failed to read database.");
}

void Database_open(const char *filename, char mode)
{
	// allocates memory on the heap to the global conn variable
	conn = malloc(sizeof(struct Connection));

	if (!conn)
		die("Memory error");
	
	// allocates memory for a database to that connection
	conn->db = malloc(sizeof(struct Database));
	if (!conn->db)
		die("Memory error");

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
		if (conn->file)
			Database_load(conn);
	}

	if (!conn->file) 
		die("Failed to open the file.");
}

void Database_close()
{
	if (conn) {
		if (conn->file)
			fclose(conn->file);
		if (conn->db)
			free(conn->db);
		free(conn);
	}
}

void Database_write()
{
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die("Failed to write database.");
	
	rc = fflush(conn->file);
	if (rc == -1)
		die("Cannot flush database.");
}

void Database_create()
{
	int i = 0;
	for (i = 0; i < MAX_ROWS; i++) {
		conn->db->rows[i] = (struct Address){.id = i, .set = 0 };
	}
}

void Database_set(int id, const char *name, const char
		*email)
{
	struct Address *addr = &conn->db->rows[id];
	if (addr->set)
		die("Already set, delete this row first.");

	addr->set = 1;

	char *res = strncpy(addr->name, name, MAX_DATA);
	addr->name[MAX_DATA - 1] = '\0';
	if (!res)
		die("Name copy failed.");

	res = strncpy(addr->email, email, MAX_DATA);
	addr->email[MAX_DATA - 1] = '\0';
	if (!res)
		die("Email copy failed.");
	
	printf("set: ");
	Address_print(addr);
}

void Database_get(int id)
{
	struct Address *addr = &conn->db->rows[id];
	if (addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set.");
	}
}

void Database_delete(int id)
{
	struct Address *addr = &conn->db->rows[id];
	if (addr->set) {
		struct Address del_addr = { .id = id, .set = 0 };
		conn->db->rows[id] = del_addr;
		printf("deleted: ");
		Address_print(addr);
	} else {
		die("ID is already empty.");
	}
}

void Database_list()
{
	int i = 0;
	struct Database *db = conn->db;

	for (i = 0; i < MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];
		if (cur->set)
			Address_print(cur);
	}
}

int main (int argc, char *argv[])
{
	if (argc < 3) 
		die("USAGE: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];

	Database_open(filename, action);

	int id = 0;
	
	if (argc > 3) id = atoi(argv[3]); 
	if (id >= MAX_ROWS) die("There're not that many records.");

	switch (action) {
		case 'c':
			Database_create();
			Database_write();
			printf("Created database, written to file: %s\n", filename);
			break;
		case 's':
			if (argc != 6)
				die("Need id, name, email to set.");
			Database_set(id, argv[4], argv[5]);
			Database_write();
			break;
		case 'g':
			if (argc != 4)
				die("Need an id to get.");
			Database_get(id);
			break;
		case 'd':
			if (argc != 4)
				die("Need an id to delete.");
			Database_delete(id);
			Database_write();
			break;
		case 'l':
			Database_list();
			break;
		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close();

	return 0;
}

