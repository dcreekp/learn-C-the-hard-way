#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512   // using the C pre-processor to create constant settings
#define MAX_ROWS 100

struct Address { 
// a struct with four fields
	int id;
	int set;
	char name[MAX_DATA];     // creating a piece of data that is fixed in size
	char email[MAX_DATA];
};

struct Database {
// creating a database with the Address struct as a "table"
	struct Address rows[MAX_ROWS];  // also fixed in size, db can have 100 lines
};

struct Connection {
// a struct that contains the Database struct and a file to record the db
// FILE is a c data structure with methods to interact with fopen fclose fread	
	FILE *file;					// from stdio.h
	struct Database *db;
};

void die(const char *message)
// a function to call to end the program with an error message
{
	if(errno) {  // errno is an integer indicating an error from errno.h
		perror(message);
	}
	else {
		printf("ERROR: %s\n", message);
	}
	exit(1); // exit with a non-zero aborts the program and cleans up 
}

void Address_print(struct Address *addr)
// function to print the id name and email of an instance of Address
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
// function to read the database and create error message if unsuccessful
// fread returns the number of data elements it was able to read
// fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
{
	int read_count = fread(conn->db, sizeof(struct Database), 1, conn->file);
	// attempt to read 1 data element that is sizeof(struct Database) bytes long
	if(read_count != 1) die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
// populates the connection struct, and the database struct
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	// creates a memory space in the heap for the Connection struct
	if(!conn) die("Memory error.");

	conn->db = malloc(sizeof(struct Database));
	// creates memory space in heap for the Database struct
	if(!conn->db) die("Memory error.");

	// assigns the file depending on which mode the file needs to be opened
	if(mode == 'c') {
		conn->file = fopen(filename, "w");
	}
	else {
		conn->file = fopen(filename, "r+");

		// reads the file
		if(conn->file) {
			Database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open the file.");
	
	return conn;
}

void Database_close(struct Connection *conn)
// closes the database and releases the allocated memory
{
	if(conn) {
		if(conn->file) fclose(conn->file); // closes the FILE
		if(conn->db) free(conn->db);       // releases the allocated memory
		free(conn);
	}
}

void Database_write(struct Connection *conn)
// writing the contents of struct Database to file
// just needs the Connection struct which contains both data elements
{
	// setting the position of the stream to the beginning of the file
	rewind(conn->file);

	// attempting to write 1 data element of length struct Database from
	// conn->db to conn->file
	// the position of the stream is advanced by the number of bytes written
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to write database.");

	// if there is any unwritten data in the output buffer it is written to file
	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database.");
}

void Database_create(struct Connection *conn)
// creates a database as a list of empty Addresses
{
	int i = 0;

	for(i = 0; i < MAX_ROWS; i++) {
		// make a prototype to initialise it
		// Address is given data elements (uses dot notation because addr is not
		// a pointer
		struct Address addr = {.id = i, .set = 0};
		// then just assign it 
		conn->db->rows[i] = addr;
	}

}

void Database_set(
	struct Connection *conn, int id, const char *name, const char *email)
// for the given address id set the name and email
{
	// nested struct pointers to get the address of rows[id]
	struct Address *addr = &conn->db->rows[id];
	// check to not overwrite if set=1 record already exists
	if(addr->set) die("Already set, delete it first.");

	// now setting the addr as set = 1
	addr->set = 1;

	char *res;
	// strncpy copies the string from name to addr->name
	// it also ensures that at most MAX_DATA-1 bytes are copied because that is
	// the size allocated to addr->name
	res = strncpy(addr->name, name, MAX_DATA-1);
	// the bug with strncpy is that if the source does not have a terminating
	// null-byte the destination won't either, so need to manually add it.
	addr->name[MAX_DATA-1] = '\0';
	if(!res) die("Name copy failed.");

	res = strncpy(addr->email, email, MAX_DATA-1);
	addr->email[MAX_DATA-1] = '\0';
	if(!res) die("Email copy failed.");
}

void Database_get(struct Connection *conn, int id)
// gets the database record by id and prints it
{
	// again nested struct pointers to get to the address of the record
	struct Address *addr = &conn->db->rows[id];

	if(addr->set) { // checks if addr->set is 1 (not 0 which means not NULL)
		Address_print(addr);
	}
	else {
		die("ID is not set.");
	}
}

void Database_delete(struct Connection *conn, int id)
// deletes a record on the database by id
{
	// creates a new empty record and sets it to the given id
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
// prints to stdout a list of records in the database
{
	int i = 0;
	// creates pointer to the db
	struct Database *db = conn->db;

	for(i = 0; i < MAX_ROWS; i++) {
		// creates a pointer to the memory address of the current row
		struct Address *cur = &db->rows[i];

		if(cur->set) { // prints the current row if it exists
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if(argc > 3) id = atoi(argv[3]); // atoi converts a string to an integer
	if(id >= MAX_ROWS) die("There's not that many records.");

	switch(action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;

		case 'g':
			if(argc != 4) die("Need an id to get");

			Database_get(conn, id);
			break;

		case 's':
			if(argc != 6) die("Need id, name, email to set");

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if(argc != 4) die("Need an id to delete");

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;

		default:
			die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);

	return 0;
}
