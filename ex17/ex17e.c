#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

/* The die function needs to be augmented to let you pass the conn variable, so
 it can close it and clean up
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

void Database_close(struct Connection *conn); // forward declaration

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void die(struct Connection *conn, const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	Database_close(conn);
	exit(1);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die(conn, "Failed to load database");
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn)
		die(conn, "Memory error");

	conn->db = malloc(sizeof(struct Database));
	if (!conn->db)
		die(conn, "Memory error");

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
		if (conn->file)
			Database_load(conn);
	}

	if (!conn->file)
		die(conn, "Failed to open the file");

	return conn;
}

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

void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die(conn, "Failed to write database.");

	rc = fflush(conn->file);
	if (rc == -1)
		die(conn, "Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
	int i = 0;

	for (i = 0; i < MAX_ROWS; i++) {
		struct Address addr = { .id = i, .set = 0 };
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name,
		const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	if (addr->set)
		die(conn, "Already set, delete it first");
	addr->set = 1;

	char *res = strncpy(addr->name, name, MAX_DATA);
	addr->name[MAX_DATA - 1] = '\0';
	if (!res)
		die(conn, "Name copy failed");

	res = strncpy(addr->email, email, MAX_DATA);
	addr->email[MAX_DATA - 1] = '\0';
	if (!res)
		die(conn, "Email copy failed");

	printf("set: %d %s %s\n", id, name, email);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if (addr->set) {
		Address_print(addr);
	} else {
		die(conn, "Id is not set");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if (addr->set) {
		//struct Address del_addr = { .id = id, .set = 0 };
		conn->db->rows[id] = (struct Address){ .id = id, .set = 0 };
		printf("deleted: ");
		Address_print(addr);
	} else {
		die(conn, "Id is already empty");
	}
}

void Database_list(struct Connection *conn)
{
	struct Database *db = conn->db;
	int i = 0;

	for (i = 0; i < MAX_ROWS; i++) {
		struct Address *addr = &db->rows[i];
		if (addr->set)
			Address_print(addr);
	}
}

int main(int argc, char *argv[])
{
	//struct Connection *empty = NULL;

	if (argc < 3)
		die(NULL, "USAGE: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);

	int id = 0;
	if (argc > 3) id = atoi(argv[3]);
	if (id >= MAX_ROWS) die(NULL, "There're not that many records");

	switch (action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			printf("Created database file: %s\n", filename);
			break;
		case 's':
			if (argc != 6)
				die(conn, "Need id, name, email to set");
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		case 'g':
			if (argc != 4)
				die(conn, "Need an id to get");
			Database_get(conn, id);
			break;
		case 'd':
			if (argc != 4)
				die(conn, "Need an id to delete");
			Database_delete(conn, id);
			Database_write(conn);
			break;
		case 'l':
			Database_list(conn);
			break;
		default:
			die(conn, "Invalid action: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);

	return 0;
}
