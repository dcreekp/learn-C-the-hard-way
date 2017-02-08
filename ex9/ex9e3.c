#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 1;

	while (i) {
		printf("%d\n", i-1);
		i++;
		if (i < 26) {
			continue;
		} else {
			i = 0;
		}
	}
}

