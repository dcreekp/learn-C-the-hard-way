#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* Get a hex editor and open up ex18, and then find the sequence of hex digits
 * that start a function to see if you can find the function in the raw program.
 * Find other random things in your hex editor and change them. Rerun your
 * program and see what happens.
 * Strings you find are the easiest things to change.
 */

// using vim command :%!xxd gets you into hexeditor mode :%!xxd -r gets you out
// the xxd program gets run inside vim
// need to :w in normal mode for the compiler to work

// the die function
void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

// a typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb)(int a, int b);


// the classic bubble sort function; it uses compare_cb to do the sorting
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
			if (cmp(target[j], target[j+1]) > 0) {
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

// used to test that the sorting is working correctly by sorting and printing
void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);

	if (!sorted)
		die("Failed to sort as requested");

	for (i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);
}

int main(int argc, char *argv[])
{
	if (argc < 2) die("USAGE: ex18 <number> <number> <number> <number> ... ");

	int count = argc - 1;
	int i = 0;
	// inputs will point to the second pointer in argv[], ie argv[1]
	char **inputs = argv + 1;

	// creates new memory space for pointer to ints
	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error");

	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}
	
	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);

	free(numbers);

	return 0;				
}
