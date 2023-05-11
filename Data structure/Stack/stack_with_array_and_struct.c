#include <stdio.h>

#define STACK_SIZE 8

int 	stack_arr[STACK_SIZE];
int 	top;
int     is_empty();
int     is_full();   
int     pop(int *stack_err);
void 	push(int *stack_arr, int data);

struct _Stack{
	int 	(*is_empty)();
	int 	(*is_full)();
	int     (*pop)(int*);
	void    (*push)(int*, int);
};

typedef struct _Stack Stack;

Stack stack = {
	.is_empty = is_empty,
	.is_full = is_full,
	.pop = pop,
	.push = push
};

int main() {
	// push items into the stack 
	stack.push(stack_arr, 3);
	stack.push(stack_arr, 5);
	stack.push(stack_arr, 9);
	stack.push(stack_arr, 1);
	stack.push(stack_arr, 12);
	stack.push(stack_arr, 15);

    // print stack data 
    while(!is_empty()) {
        int data = pop(stack_arr);
        printf("%d ",data);
    }
    printf("\n");
    printf("Stack full: %s\n" , is_full()?"true":"false");
    printf("Stack empty: %s\n" , is_empty()?"true":"false");
   	return 0;
}

int is_empty() {
    if(top == -1) return 1;
    else return 0;
}

int is_full() {
	if(top == STACK_SIZE) return 1;
	else return 0;
}

int pop(int *stack_arr) {
   	int data;
	
    if(!is_empty()) {
		data = stack_arr[top];
		stack_arr[top] = 0;// Reset value of stack[top]
		top = top - 1;   
		return data;
    } else {
      printf("Could not retrieve data, Stack is empty\n");
	  return NULL;
    }
}

void push(int *stack_arr, int data) {
    if(!is_full()) {
        top = top + 1;   
        stack_arr[top] = data;
    } else {
        printf("Could not insert data, Stack is full\n");
    }
}