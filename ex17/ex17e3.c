#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

/*
 * Add some more fields to Address and make them searchable
 * And
 * Change the code to accept parameters for MAX_DATA and MAX_ROWS, store them in
 * the Database struct, and write that to the file, thus creating a database 
 * that can be arbitrarily sized.
 */

struct Address {
	char *name;
	char *email;
	char *location;
	int age;
	int set;
	int id;
};

struct Database {
	struct Address **rows;
	int MAX_DATA;
	int MAX_ROWS;
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Database_close(struct Connection *conn);

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

void Address_print(struct Address *addr)
{
	printf("%d %s %d %s %s\n", addr->id, addr->name, addr->age, addr->email,
			addr->location);
}

void Database_load(struct Connection *conn)
{
	size_t i = 0;
	int rc = 0;

	assert(conn->file && conn->db);
	if (!(conn->file && conn->db))
		die(conn, "Database load: Invalid connection info");

	rc = fread(&conn->db->MAX_DATA, sizeof(conn->db->MAX_DATA), 1, conn->file);
	if (rc != 1)
		die(conn, "Database load: could not read MAX_DATA");
	rc = fread(&conn->db->MAX_ROWS, sizeof(conn->db->MAX_ROWS), 1, conn->file);
	if (rc != 1)
		die(conn, "Database load: could not read MAX_ROWS");

	conn->db->rows = (struct Address**)malloc(sizeof(struct Address*) * conn->db->MAX_ROWS);

	assert(conn->db->rows);
	if (!conn->db->rows)
		die(conn, "Database load: MAX_ROWS Address structure");

	for (i = 0; i < conn->db->MAX_ROWS; i++) {

		conn->db->rows[i] = (struct Address*)malloc(sizeof(struct Address));
		struct Address *row = conn->db->rows[i];

		rc = fread(&row->id, sizeof(row->id), 1, conn->file);
		if (rc != 1)
			die(conn, "Database load:  couldn't read ID");
		rc = fread(&row->set, sizeof(row->set), 1, conn->file);
		if (rc != 1)
			die(conn, "Database load: couldn't read set");
		rc = fread(&row->age, sizeof(row->age), 1, conn->file);
		if (rc != 1)
			die(conn, "Database load: couldn't read age");

		size_t str_size = sizeof(char) * conn->db->MAX_DATA;
		row->name = malloc(str_size);
		row->email = malloc(str_size);
		row->location = malloc(str_size);

		assert(row->name && row->email && row->location);
		if (!(row->name && row->email && row->location))
			die(conn, "Database load: failed to allocate address strings");

		rc = fread(row->name, str_size, 1, conn->file);
		if (rc != 1)
			die(conn, "Database load: couldn't read name");
		rc = fread(row->email, str_size, 1, conn->file);
		if (rc != 1)
			die(conn, "Database load: couldn't read email");
		rc = fread(row->location, str_size, 1, conn->file);
		if (rc != 1)
			die(conn, "Database load: couldn't read location");
	}
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn)
		die(conn, "Memory Error");

	conn->db = malloc(sizeof(struct Database));
	if (!conn->db)
		die(conn, "Memory Error");

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
		if (conn->file)
			Database_load(conn);
	}

	if (!conn->file)
		die(conn, "Failed to open file");

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
			free(conn->db->rows);
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
	int rc = 0;
	size_t i = 0;
	size_t str_size = 0;

	rewind(conn->file);
	
	rc = fwrite(&conn->db->MAX_DATA, sizeof(conn->db->MAX_DATA), 1, conn->file);
	if (rc != 1)
		die(conn, "Database write: failed to write MAX_DATA");
	rc = fwrite(&conn->db->MAX_ROWS, sizeof(conn->db->MAX_ROWS), 1, conn->file);
	if (rc != 1)
		die(conn, "Database write: failed to write MAX_ROWS");

	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *row = conn->db->rows[i];
		str_size = sizeof(char) * conn->db->MAX_DATA;

		rc = fwrite(&row->id, sizeof(row->id), 1, conn->file);
		if (rc != 1)
			die(conn, "Database write: failed to write Address(ID)");
		rc = fwrite(&row->set, sizeof(row->set), 1, conn->file);
		if (rc != 1)
			die(conn, "Database write: failed to write Address(set)");
		rc = fwrite(&row->age, sizeof(row->age), 1, conn->file);
		if (rc != 1)
			die(conn, "Database write: failed to write Address(age)");

		rc = fwrite(row->name, str_size, 1, conn->file);
		if (rc != 1)
			die(conn, "Database write: failed to write Address(name)");
		rc = fwrite(row->email, str_size, 1, conn->file);
		if (rc != 1)
			die(conn, "Database write: failed to write Address(email)");
		rc = fwrite(row->location, str_size, 1, conn->file);
		if (rc != 1)
			die(conn, "Database write: failed to write Address(location)");
	}

	rc = fflush(conn->file);
	if (rc == -1)
		die(conn, "Database write: Cannot flush database");
}

void Database_create(struct Connection *conn, int MAX_DATA, int MAX_ROWS)
{
	size_t i = 0;

	conn->db->MAX_DATA = MAX_DATA;
	conn->db->MAX_ROWS = MAX_ROWS;

	conn->db->rows = (struct Address**)malloc(sizeof(struct Address*) * MAX_ROWS);

	for (i = 0; i < MAX_ROWS; i++) {
		conn->db->rows[i] = (struct Address*)malloc(sizeof(struct Address));

		struct Address *row = conn->db->rows[i];

		row->id = i;
		row->set = 0;
		row->age = '\0';

		row->name = (char *)malloc(MAX_DATA);
		row->email = (char *)malloc(MAX_DATA);
		row->location = (char *)malloc(MAX_DATA);

		row->name = (char *)memset(row->name, ' ', MAX_DATA);
		row->email = (char *)memset(row->email, ' ', MAX_DATA);
		row->location = (char *)memset(row->location, ' ', MAX_DATA);
	}
}

void Database_set(struct Connection *conn, int id, char *name, int age,
		char *email, char *location)
{
	struct Address *addr = conn->db->rows[id];
	if (addr->set)
		die(conn, "ID is already set, delete it first");

	addr->set = 1;
	addr->age = age;

	int MAX_DATA = conn->db->MAX_DATA;

	addr->name = malloc(sizeof(char) * MAX_DATA);
	addr->email = malloc(sizeof(char) * MAX_DATA);
	addr->location = malloc(sizeof(char) * MAX_DATA);

	char *res = strncpy(addr->name, name, MAX_DATA);
	addr->name[MAX_DATA - 1] = '\0';
	if (!res) die(conn, "Database set: name copy failed");
	res = strncpy(addr->email, email, MAX_DATA);
	addr->email[MAX_DATA - 1] = '\0';
	if (!res) die(conn, "Database set: email copy failed");
	res = strncpy(addr->location, location, MAX_DATA);
	addr->location[MAX_DATA - 1] = '\0';
	if (!res) die(conn, "Database set: location copy failed");

	printf("set: ");
	Address_print(addr);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];

	if (addr->set) {
		Address_print(addr);
	} else {
		die(conn, "Database get: this is ID is not set");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];
	
	addr->set = 0;
	addr->age = '\0';
	addr->name = memset(addr->name, ' ', conn->db->MAX_DATA);
	addr->email = memset(addr->email, ' ', conn->db->MAX_DATA);
	addr->location = memset(addr->location, ' ', conn->db->MAX_DATA);

	printf("deleted: %d\n", id);
}

void Database_list(struct Connection *conn)
{
	size_t i = 0;
	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		if (conn->db->rows[i]->set) {
			struct Address *cur = conn->db->rows[i];
			Address_print(cur);
		}
	}
}

int Database_find_name(struct Connection *conn, char *name)
{
	size_t i = 0;
	int found = 0;
	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *cur = conn->db->rows[i];
		if (cur->set && strcmp(cur->name, name) == 0) {
			printf("found: ");
			Address_print(cur);
			found = 1;
		}
	}		
	return found;
}

int Database_find_age(struct Connection *conn, int age)
{
	size_t i = 0;
	int found = 0;
	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *cur = conn->db->rows[i];
		if (cur->set && cur->age == age) {
			printf("found: ");
			Address_print(cur);
			found = 1;
		}
	}
	return found;
}

int Database_find_email(struct Connection *conn, char *email)
{
	size_t i = 0;
	int found = 0;
	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *cur = conn->db->rows[i];
		if (cur->set && strcmp(cur->email, email) == 0) {
			printf("found: ");
			Address_print(cur);
			found = 1;
		}
	}
	return found;
}

int Database_find_location(struct Connection *conn, char *location)
{
	size_t i = 0;
	int found = 0;
	for (i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *cur = conn->db->rows[i];
		if (cur->set && strcmp(cur->location, location) == 0) {
			printf("found: ");
			Address_print(cur);
			found = 1;
		}
	}
	return found;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		die(NULL, "USAGE: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	
	switch (action) {
		case 'c':
			if (argc < 5)
				die(conn, "Need to MAX_DATA and MAX_ROWS to create db");
			int MAX_DATA = atoi(argv[3]);
			int MAX_ROWS = atoi(argv[4]);
			Database_create(conn, MAX_DATA, MAX_ROWS);
			Database_write(conn);
			break;
		case 's':
			if (argc < 8)
				die(conn, "Need ID, name, age, email, location to set");
			int id = atoi(argv[3]);
			char *name = argv[4];
			int age = atoi(argv[5]);
			char *email = argv[6];
			char *location = argv[7];
			Database_set(conn, id, name, age, email, location);
			Database_write(conn);
			break;
		case 'g':
			if (argc < 4)
				die(conn, "Need ID to get");
			id = atoi(argv[3]);
			Database_get(conn, id);
			break;
		case 'd':
			if (argc < 4)
				die(conn, "Need ID to delete");
			id = atoi(argv[3]);
			Database_delete(conn, id);
			Database_write(conn);
			break;
		case 'l':
			Database_list(conn);
			break;
		case 'f':
			if (argc < 5)
				die(conn, "Specify <field> <item>");
			char *field = argv[3];
			char *item = argv[4];
			int found = 0;
			if (strcmp(field, "name") == 0) {
				found = Database_find_name(conn, item);
			} else if (strcmp(field, "age") == 0) {
				found = Database_find_age(conn, atoi(item));
			} else if (strcmp(field, "email") == 0) {
				found = Database_find_email(conn, item);
			} else if (strcmp(field, "location") == 0) {
				found = Database_find_location(conn, item);
			} else {
				die(conn, "Invalid field: must be name, age, email or location");
			}
			if (!found)
				printf("%s not found in Database field %s\n", item, field);
			break;
		default:
			die(conn, "Invalid: c=create, s=set, g=get, d=del, l=list, f=find");
	}

	Database_close(conn);
	
	return 0;
}

