#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* Pass in the wrong function for the compare_cb and see what the C compiler
 * complains about.
 * Pass in NULL and watch your program seriously bite it. Then, run the debugger
 * and see what that reports.
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

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	int *target = malloc(count * sizeof(int));
	if (!target) die("Memory error");

	memcpy(target, numbers, count *sizeof(int));

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

void print_nothing()
{
	printf("this function just prints nothing");
}

int wrong_order()
{
	return 8;
}

void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);
	if (!sorted) die("Failed to sort as requested");

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
	if (!numbers) die("Memory error");
	
	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	test_sorting(numbers, count, strange_order);
	test_sorting(numbers, count, sorted_order);
	
	test_sorting(numbers, count, print_nothing);
	// will result in a compiler warning saying that the print_nothing function
	// is not the type of function it is expecting
	// but the program still runs just returns the printed words
	
	test_sorting(numbers, count, wrong_order);
	// this function doesn't sort anything but is of the right type so the
	// compiler gives no warning and the program will just work but in an
	// unexpected way, it will always sort as it returns an int greater than 0

	test_sorting(numbers, count, NULL);
	// the compiler does not complain about this at all but it leads to a
	// segfault trying to call a function that apparently has an address where
	// null resides 0x0
	
	free(numbers);

	return 0;
}

