#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s", message);
	}
	exit(1);
}

// typedef creates a fake type in this case for a function pointer
typedef int (*compare_cb)(int a, int b);

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));
	if (!target) die("Memory error");

	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < count; i++) {
		for (j = 0; j < count - 1; j++) {
			if (cmp(target[j], target[j+1]) > 0){
				temp = target[j+1];
				target[j+1] = target[j];
				target[j] = temp;
			}
		}
	}
	return target;
}

int sorted_order(int a, int b)
{
	return (a > b) - (a < b);
}

int reverse_order(int a, int b)
{
	return (a < b) - (a > b);
}

int strange_order(int a, int b)
{
	if (a == 0 || b == 0) {
		return 0;
	} else {
		return a % b;
	}
}

void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = malloc(count * sizeof(int));

	sorted = bubble_sort(numbers, count, cmp);

	for (i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");
}

void dump(compare_cb cmp)
{
	int i = 0;
	unsigned char *data = (unsigned char *)cmp;

	// gets the character bytes of cmp, a function pointer and
	// casts it into an unsigned char
	// converting the code into character data, treating code like it's data
	for (i = 0; i < 125; i++) {
		printf("%02x:", data[i]);
	}
	// it will print off the raw assembler byte code of the function cmp
	printf("\n");
}

void destroy(compare_cb cmp)
{
	int i =0;
	unsigned char *data = (unsigned char *)cmp;

	// this tries to overwrite the code
	// luckily this os segfaults instead of replacing the binary code with ints 
	for (i = 0; i < 1; i++) {
		data[i] = i;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) die("USAGE: ex18 <number> <number> <number> <number> ...");

	int count = argc - 1;
	char **inputs = argv + 1;
	int i = 0;

	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error");

	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);
	
	dump(sorted_order);
	dump(reverse_order);
	destroy(sorted_order);

	free(numbers);

	return 0;
}


		
