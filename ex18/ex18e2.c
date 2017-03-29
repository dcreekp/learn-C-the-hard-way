#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Write another sorting algorithm, then change test_sorting so that it takes
 * both an arbitrary sort function and the sort function's callback comparison.
 * Use it to test both your algorithms.
 */

void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

typedef int (*compare_cb)(int a, int b);
typedef int *(*sort_cb)(int *numbers, int count, compare_cb cmp);

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int temp = 0;
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

int *insertion_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	int *target = malloc(count * sizeof(int));
	if (!target) die("Memory error");

	memcpy(target, numbers, count * sizeof(int));

	for (i = 1; i < count; i++) {
		for (j = i; j > 0; j--) {
			if (cmp(target[j-1], target[j]) > 0) {
				temp = target[j];
				target[j] = target[j-1];
				target[j-1] = temp;
			} else {
				break;
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

void test_sorting(int *numbers, int count, sort_cb sort, compare_cb cmp)
{	
	int i = 0;
	int *sorted = malloc(count * sizeof(int));
	if (!sorted) die("Memory error");

	sorted = sort(numbers, count, cmp);

	for (i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);
}

int main(int argc, char *argv[])
{
	if (argc < 2) die("USAGE: ex18 <number> <number> <number> <number> ...");

	int i = 0;
	int count = argc - 1;
	char **inputs = argv + 1;
	int *numbers = malloc(count * sizeof(int));

	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	test_sorting(numbers, count, bubble_sort, sorted_order);
	test_sorting(numbers, count, bubble_sort, reverse_order);
	test_sorting(numbers, count, bubble_sort, strange_order);

	test_sorting(numbers, count, insertion_sort, sorted_order);
	test_sorting(numbers, count, insertion_sort, reverse_order);
	test_sorting(numbers, count, insertion_sort, strange_order);

	free(numbers);

	return 0;
}


