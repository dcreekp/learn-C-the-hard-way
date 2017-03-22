#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// #define MAX_DATA 512
// #define MAX_ROWS 100

/*
  Change the code to accept parameters for MAX_DATA and MAX_ROWS, store them in
  the Database struct, and write that to the file, thus creating a database that
  can be arbitrarily sized.
*/

struct Address {
	int id;
	int set;
	char *name;    	// note that a pointer can remain flexible while an empty
	char *email;	// name[] without specifying the number of rows fails
};

struct Database {
	int MAX_DATA;
	int MAX_ROWS;
	struct Address **rows; 	// declaring a pointer to pointers
							// will be used as if it is an array of pointers
};

struct Connection {
	FILE *file;
	struct Database *db;
};

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
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	size_t i = 0;
	int rc = 0;

	assert(conn->db && conn->file);
	if (!(conn->db && conn->file))
		die("Database load: Invalid Connection Info");
	
	// each database will have two int values read those first
	// the first parameter of fread is the location/address of whatever needs to
	// be read
	rc = fread(&conn->db->MAX_DATA, sizeof(conn->db->MAX_DATA), 1, conn->file);
	if (rc != 1)
		die("Database load: Couldn't read MAX_DATA");
	rc = fread(&conn->db->MAX_ROWS, sizeof(conn->db->MAX_ROWS), 1, conn->file);
	if (rc != 1)
		die("Database load: Couldn't read MAX_ROWS");

	// creates the pointer rows
	// typecasted as a pointer pointing to pointers that point to Address
	// and is allocated memory equal to space for pointers multiplied by
	// MAX_ROWS
	conn->db->rows = (struct Address**)malloc(sizeof(struct Address*) * conn->db->MAX_ROWS);
	
	// printf("Sizeof *conn->db->rows is %lu\n", sizeof(*conn->db->rows));
	assert(conn->db->rows);
	if (!conn->db->rows) 
		die("Database load: Could not MAX_ROWS Address structures");

	// now load each address structure
	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		// rows[i] is typecasted as a pointer to struct Address, it is allocated 
		// memory space to fit struct Address
		conn->db->rows[i] = (struct Address*)malloc(sizeof(struct Address));
		// creating a temporary pointer to the same data
		struct Address *row = conn->db->rows[i];
		
		rc = fread(&row->id, sizeof(row->id), 1, conn->file);
		if (rc != 1)
			die("Database load: Could not read Address::id");
		rc = fread(&row->set, sizeof(row->set), 1, conn->file);
		if (rc != 1)
			die("Database load: Could not read Address::set");
		
		// allocate two buffers large enough for our data
		// printf("*row->name sizeof is %d\n", sizeof(*row->name));
		// *row->name is the pointer of the first element in name
		// so it is allocating the size: MAX_DATA multiplied by one char
		row->name = malloc(conn->db->MAX_DATA * sizeof(*row->name));
		row->email = malloc(conn->db->MAX_DATA * sizeof(*row->email));
		assert(row->name && row->email);
		if (!(row->name && row->email))
			die("Database load: Failed to allocate Address strings");

		// the 
		rc = fread(row->name, conn->db->MAX_DATA * sizeof(*row->name), 1, conn->file);
		if (rc != 1)
			die("Database load: Failed to read Address::name");
		rc = fread(row->email, conn->db->MAX_DATA * sizeof(*row->email), 1, conn->file);
		if (rc != 1)
			die("Database load: Failed to read Address::email");
	}
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error");

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error");

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
		if (conn->file)
			Database_load(conn);
	}

	if (!conn->file) die("Failed to open the file.");

	return conn;
}

void Database_close(struct Connection *conn)
{
	size_t i = 0;

	if (conn) {
		if (conn->db && conn->db->rows) {
			for (i = 0; i < conn->db->MAX_ROWS; i++) {
				struct Address *cur = conn->db->rows[i];
				free(cur);
			}
		}
		if (conn->file) 
			fclose(conn->file);
		if (conn->db)
			free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);
	size_t i = 0;
	int rc = 0;

	// all of these writes the address of the pointers to the file
	// writing MAX_DATA and MAX_ROWS to the file first
	// remember the first parameter of fwrite is the location/address of
	// whatever needs to be written
	rc = fwrite(&conn->db->MAX_DATA, sizeof(conn->db->MAX_DATA), 1, conn->file);
	if (rc != 1)
		die("Database write: Failed to write MAX_DATA");
	rc = fwrite(&conn->db->MAX_ROWS, sizeof(conn->db->MAX_ROWS), 1, conn->file);
	if (rc != 1)
		die("Database write: Failed to write MAX_ROWS");

	// writing the rows of Address
	for ( i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *row = conn->db->rows[i];
		rc = fwrite(&row->id, sizeof(row->id), 1, conn->file);
		if (rc != 1)
			die("Database write: Failed to write Address(id)");
		rc = fwrite(&row->set, sizeof(row->set), 1, conn->file);
		if (rc != 1)
			die("Database write: Failed to write Address(set)");
		// allocates a memory size that is char multiplied by MAX_DATA
		// to row->name which is already a pointer (an address)
		rc = fwrite(row->name, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
		if (rc != 1)
			die("Database write: Failed to write Address(name)");
		rc = fwrite(row->email, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
		if (rc != 1)
			die("Database write: Failed to write Address(email)");
	}
	
	rc = fflush(conn->file);
	if (rc == -1)
		die("Database write: Cannot flush database.");
}

void Database_create(struct Connection *conn, int MAX_DATA, int MAX_ROWS)
{
	int i = 0;
	conn->db->MAX_DATA = MAX_DATA;
	conn->db->MAX_ROWS = MAX_ROWS;
	// creating a pointer at conn->db->rows
	// this allocates memory to conn->db->rows which is a pointer/array of
	// pointers to struct Address. The size of the allocated memory is; the size
	// of a pointer to struct Address multiplied by MAX_ROWS
	conn->db->rows = (struct Address**)malloc(sizeof(struct Address*) * MAX_ROWS);

	for (i = 0; i < MAX_ROWS; i++) {
		conn->db->rows[i] = (struct Address*)malloc(sizeof(struct Address));
		conn->db->rows[i]->id = i;
		conn->db->rows[i]->set = 0;
		// declaring the pointer conn->db->rows[i]->name; as a pointer to char
		// type with the memory space of MAX_DATA
		conn->db->rows[i]->name = (char *)malloc(conn->db->MAX_DATA);
		// memset fills the memory space of pointer conn->db->rows[i]->name with 
		// ' ' up to the the number of bytes expressed by MAX_DATA, basically it
		// fills the first n bytes of the memory space with a constant byte  
		conn->db->rows[i]->name = (char *)memset(conn->db->rows[i]->name, ' ', conn->db->MAX_DATA);
		conn->db->rows[i]->email = (char *)malloc(conn->db->MAX_DATA);
		conn->db->rows[i]->email = (char *)memset(conn->db->rows[i]->email, ' ', conn->db->MAX_DATA);
	}
}

void Database_set(struct Connection *conn, int id, const char *name, 
		const char *email)
{
	if (!(conn && conn->db && conn->db->rows && conn->db->rows[id])) return;

	if (conn->db->MAX_ROWS < id)
		die("ID exceeds database row capacity");

	struct Address *addr = conn->db->rows[id];
	int MAX_DATA = conn->db->MAX_DATA;

	if (addr->set)
		die("Already set, delete row first");
	
	addr->set = 1;
	// need to malloc for name and email because they are now pointers
	// instead of arrays which alredy had defined size 
	addr->name = malloc(sizeof(char) * MAX_DATA);
	addr->email = malloc(sizeof(char) * MAX_DATA);

	char *res = strncpy(addr->name, name, MAX_DATA);
	addr->name[MAX_DATA - 1] = '\0';
	if (!res) die("Name copy failed");

	res = strncpy(addr->email, email, MAX_DATA);
	addr->email[MAX_DATA - 1] = '\0';
	if (!res) die("Email copy failed");

	printf("set: ");
	Address_print(addr);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];

	if (addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set.");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];

	addr->set = 0;
	addr->name = memset(addr->name, ' ', conn->db->MAX_DATA);
	addr->email = memset(addr->email, ' ', conn->db->MAX_DATA);

	printf("deleted: %d\n", id);
}

void Database_list(struct Connection *conn)
{
	size_t i = 0;

	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *cur = conn->db->rows[i];
		if (cur->set)
			Address_print(cur);
	}
}


int main(int argc, char *argv[])
{
	if (argc < 3)
		die("USAGE: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;
	
	switch (action) {
		case 'c':
			if (argc < 5) 
				die("Need to specify MAX_DATA, MAX_ROWS");
			// protecting CPU capacity: there is a limit to memory RAM can hold
			unsigned long MAX_DATA = atoi(argv[3]);
			unsigned long MAX_ROWS = atoi(argv[4]);
			if (MAX_DATA > 2000)
				die("Allowed MAX_DATA = 2000");
			if (MAX_ROWS > 1000000)
				die("Allowed MAX_ROWS = 1000000");
			Database_create(conn, MAX_DATA, MAX_ROWS);
			Database_write(conn);
			printf("Created database file: %s\n", filename);
			break;
		case 's':
			if (argc != 6)
				die("Need ID, name, email to set");
			id = atoi(argv[3]);
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		case 'g':
			if (argc != 4)
				die("Need ID to get");
			id = atoi(argv[3]);
			Database_get(conn, id);
			break;
		case 'd':
			if (argc != 4)
				die("Need ID to delete");
			id = atoi(argv[3]);	
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

