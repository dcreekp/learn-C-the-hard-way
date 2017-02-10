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
	char *name;
	char *email;
};

struct Database {
	int max_data;
	int max_rows;
	struct Address rows[];
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
	if(errno) {
		perror(message);
	}
	else {
		printf("ERROR: %s\n", message);
	}
	Database_close(conn);

	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to load database", conn);
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error", conn);

	if(mode == 'c') {
		conn->file = fopen(filename, "w"); 
	}
	else {
		conn->file = fopen(filename, "r+");
		if(conn->file) {
			Database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open the file", conn);

	return conn;
}

void Database_close(struct Connection *conn)
{
	if(conn) {
		if(conn->file) fclose(conn->file);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to write database", conn);

	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database", conn);
}

void Database_create(struct Connection *conn, const int max_data,
						const int max_rows)
{
	int i = 0;
	for(i = 0; i < max_rows; i++) {
		struct Address addr = {.id = i, .set = 0};
		conn->db->rows[i] = addr;
	}
	conn->db->max_data = max_data;
	conn->db->max_rows = max_rows;
}

void Database_set(
		struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("Already set, delete it first", conn);

	int max_data = conn->db->max_data;
	addr->set = 1;
	char *res;
	res = strncpy(addr->name, name, max_data - 1);
	if(!res) die("Name copy failed", conn);
	addr->name[max_data - 1] = '\0';

	res = strncpy(addr->email, email, max_data - 1);
	if(!res) die("Email copy failed", conn);
	addr->email[max_data - 1] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if(addr->set) {
		Address_print(addr);
	}
	else {
		die("ID is not set", conn);
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for(i=0; i < conn->db->max_rows; i++) {
		struct Address *cur = &db->rows[i];

		if(cur->set) Address_print(cur);
	}
}

int main(int argc, char *argv[])
{
	printf("just print\n");
	char *filename = argv[1];
	char action = argv[2][0];
	int max_data;
	int max_rows;
	if(action == 'c') {
		if(argv[3]) {
			max_data = atoi(argv[3]);
		}
		else {
			max_data = MAX_DATA;
		}
		if(argv[4]) {
			max_rows = atoi(argv[4]);
		}
		else {
			max_rows = MAX_ROWS;
		}
	}
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", conn);

	if(argc > 3 && action != 'c') id = atoi(argv[3]);
	if(id >= max_rows) die("There are not that many records", conn);

	switch(action) {
		case 'c':
			Database_create(conn, max_data, max_rows);
			Database_write(conn);
			break;

		case 'g':
			if(argc != 4) die("Need an id to get", conn);
			Database_get(conn, id);
			break;

		case 's':
			if(argc != 6) die("Need id, name, email to set", conn);
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;

		default:
			die("Invalid action, only: c=create, g=get, s=set, d=del, l=list",
					conn);
	}

	Database_close(conn);

	return 0;
}
