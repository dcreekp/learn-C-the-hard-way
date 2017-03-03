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

// a struct of an array of structs
struct Database {
	struct Address rows[MAX_ROWS];
};

// another struct which has a struct
struct Connection {
	FILE *file;
	struct Database *db;
};

//  function to kill program if there is an error
void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

// prints the elements of each Address struct
void Address_print(struct Address *addr)
{
	printf("%d %s %s \n", addr->id, addr->name, addr->email);
}

// function to read an existing database file onto memory
void Database_load(struct Connection *conn)
{
	// fread reads the stream conn->file to the pointer conn->db which has the
	// specified size, 1 number times
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die("Failed to read database.");
}

// function that returns a pointer to the struct Connection which is stored on
// the heap, the struct Database inside the struct Connection is also allocated
// memery on the heap
struct Connection *Database_open(const char *filename, char mode)
{
	// allocates memory on the heap for a Connection
	// conn becomes a global variable
	struct Connection *conn = malloc(sizeof(struct Connection));

	// check if the memory space is there, if not invokes die function
	if (!conn)
		die("Memory error");
	
	// allocates memory for a database to that connection
	conn->db = malloc(sizeof(struct Database));
	if (!conn->db)
		die("Memory error");

	// c is for create so it will create a new file in write mode, otherwise it
	// opens in read and write mode
	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
		if (conn->file)
			Database_load(conn);
	}

	if (!conn->file) 
		die("Failed to open the file.");

	return conn;
}

// function to ensure all allocated memory is freed at the end of the program
// and the file is closed
void Database_close(struct Connection *conn)
{
	if (conn) {
		if (conn->file)
			fclose(conn->file);
		if (conn->db)
			free(conn->db);
		free(conn);
	}
}

// this function writes the contents of the db in memory onto a file
void Database_write(struct Connection *conn)
{
	// sets the file position to the start of the fiel stream ready to the write
	// the entire db to the file from the start of the file
	rewind(conn->file);

	// fwrite writes to the stream conn->file from the pointer conn->db, 1 time
	// with a size of struct Database, it writes the entire db with its
	// modifications
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	// on success fwrite returns the number of items written 
	if (rc != 1)
		die("Failed to write database.");
	
	// fflush for input streams, discards any buffered data
	rc = fflush(conn->file);
	if (rc == -1)
		die("Cannot flush database.");
}

// this function creates an empty database with the maximum number rows already
// created with an id but initialised as not set
void Database_create(struct Connection *conn)
{
	int i = 0;
	for (i = 0; i < MAX_ROWS; i++) {
		// make a prototype to initialize each address 
		struct Address addr = {.id = i, .set = 0 };
		// then just assign each addr to a row in the db
		conn->db->rows[i] = addr;
	}
}

// this function lets the user record an address
void Database_set(struct Connection *conn, int id, const char *name, const char
		*email)
{
	// gets a pointer which points to the address of rows[id] which is accessed
	// via the pointers db and conn
	struct Address *addr = &conn->db->rows[id];
	if (addr->set)
		die("Already set, delete this row first.");

	addr->set = 1;

	// Warning bug: fix it 
	// strncpy copies a pointer to another, the second parameter to the first
	// must have third parameter to automatically fill nul bytes up to n
	char *res = strncpy(addr->name, name, MAX_DATA);
	if (!res)
		die("Name copy failed.");

	res = strncpy(addr->email, email, MAX_DATA);
	if (!res)
		die("Email copy failed.");
	
	printf("set: ");
	Address_print(addr);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];
	if (addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set.");
	}
}

// function resets the given row id as same id, and set to 0
void Database_delete(struct Connection *conn, int id)
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

void Database_list(struct Connection *conn)
{
	int i = 0;
	// getting another pointer pointng to the same memory space
	struct Database *db = conn->db;

	for (i = 0; i < MAX_ROWS; i++) {
		// setting a pointer to the address of the current row
		struct Address *cur = &db->rows[i];
		if (cur->set)
			Address_print(cur);
	}
}

int main (int argc, char *argv[])
{
	// checks for correct usage
	if (argc < 3) 
		die("USAGE: ex17 <dbfile> <action> [action params]");

	// declaring variables from argument variables
	char *filename = argv[1];
	char action = argv[2][0];

	// opening the connection to the database with the action parameter
	// (a connection between the database and the file to record the data)
	struct Connection *conn = Database_open(filename, action);

	// declaring id 
	int id = 0;
	
	// sets id to the respective argv
	// atoi converts string to integer from <stdlib.h>
	if (argc > 3) id = atoi(argv[3]); 
	if (id >= MAX_ROWS) die("There're not that many records.");

	switch (action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			printf("Created database, written to file: %s\n", filename);
			break;
		case 's':
			if (argc != 6)
				die("Need id, name, email to set.");
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		case 'g':
			if (argc != 4)
				die("Need an id to get.");
			Database_get(conn, id);
			break;
		case 'd':
			if (argc != 4)
				die("Need an id to delete.");
			Database_delete(conn, id);
			Database_write(conn);
			break;
		case 'l':
			Database_list(conn);
			break;
		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);

	return 0;
}

