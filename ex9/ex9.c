#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	
	while (i < 25) {
		printf("%d\n", i);
		i++;
	}

	// need this to add a final new line
	printf("\n");

	return 0;
}

