#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/* Go research stack data structure and write one in your favorite language, 
 * then try to do it in C
 */

struct Stack {
	int *nodes;
	int size;
	int MAX_SIZE;
};

void Free_stack(struct Stack *stack);

void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

struct Stack *New_stack(int MAX_SIZE)
{
	struct Stack *stack = malloc(sizeof(struct Stack));

	stack->nodes = malloc(sizeof(int) * MAX_SIZE);

	stack->size = 0;
	stack->MAX_SIZE = MAX_SIZE;

	return stack;
}

void Push_stack(struct Stack *stack, int value)
{
	if (stack->size < stack->MAX_SIZE) {
		stack->nodes[stack->size++] = value;
		printf("Pushed: %d\n", value);
	} else {
		Free_stack(stack);
		die("Stack is full");
	}
}

void Pop_stack(struct Stack *stack)
{
	if (stack->size > 0) {
		printf("Popped: %d\n", stack->nodes[--stack->size]);
	} else {
		Free_stack(stack);
		die("Stack is empty");
	}
}

void Free_stack(struct Stack *stack)
{
	if (stack) {
		free(stack->nodes);
		free(stack);
	}
}

int main(int argc, char *argv[])
{
	struct Stack *stack = New_stack(2);

	Push_stack(stack, 44);
	Push_stack(stack, 33);
	Push_stack(stack, 22);

	Pop_stack(stack);
	Pop_stack(stack);
	Pop_stack(stack);
	
	
	Free_stack(stack);
	return 0;
}

