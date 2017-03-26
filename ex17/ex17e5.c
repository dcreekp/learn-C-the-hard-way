#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_SIZE 100

/* Go research stack data structure and write one in your favorite language,
 * then try to do it in C.
 */

struct Stack {
	int nodes[MAX_SIZE];
	int size;
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

struct Stack *New_stack()
{
	struct Stack *stack = malloc(sizeof(struct Stack));

	stack->size = 0;

	return stack;
}

void Push(struct Stack *stack, int value)
{
	// stack->size++ gets the value and then increments
	// index of stack->size holds value, and stack->size itself is now one more
	if (stack->size < MAX_SIZE) {
		stack->nodes[stack->size++] = value;
		printf("Pushed: %d\n", value);
	} else {
		Free_stack(stack);
		die("Stack is full");
	}
}

void Pop(struct Stack *stack)
{
	// --stack->size decrements the stack->size and then gets the value
	// and also stack->size is now one less
	if (stack->size > 0) {
		printf("Popped: %d\n", stack->nodes[--stack->size]);
	} else {
		Free_stack(stack);
		die("Stack is empty");
	}
}

void Peek(struct Stack *stack)
{
	if (stack->size > 0) {
		printf("Peek: %d \n", stack->nodes[stack->size - 1]);
	} else {
		Free_stack(stack);
		die("Stack is empty");
	}
}

void List(struct Stack *stack)
{
	int i;
	if (stack->size > 0) {
		printf("List: ");
		for (i = 0; i < stack->size; i++) {
			printf("%d ", stack->nodes[i]);
		}
		printf("\n");
	} else {
		Free_stack(stack);
		die("Stack is empty");
	}
}

void Free_stack(struct Stack *stack)
{
	if (stack)
		free(stack);
}

int main(int argc, char *argv[])
{
	struct Stack *stack = New_stack();

	Push(stack, 100);
	Push(stack, 22);
	Peek(stack);

	int i = 0;
	for (i = 0; i < 10; i++) {
		Push(stack, i);
	}
	List(stack);
	Peek(stack);
	for (i = 0; i < 10; i++) {
		Pop(stack);
	}
	Pop(stack);
	Pop(stack);
	Free_stack(stack);
	return 0;
}

