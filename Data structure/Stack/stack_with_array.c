#include <stdio.h>

#define STACK_SIZE 8
  
int stack[STACK_SIZE];
int top = -1;            

int     isEmpty();
int     isFull();   
int     pop();
void    push(int data);

int main() {
	// push items into the stack 
	push(3);
	push(5);
	push(9);
	push(1);
	push(12);
	push(15);

    // print stack data 
    while(!isEmpty()) {
        int data = pop();
        printf("%d ",data);
    }
    printf("\n");
    printf("Stack full: %s\n" , isFull()?"true":"false");
    printf("Stack empty: %s\n" , isEmpty()?"true":"false");
   	return 0;
}

int isEmpty() {
    if(top == -1) return 1;
    else return 0;
}

int isFull() {
	if(top == STACK_SIZE) return 1;
	else return 0;
}

int pop() {
   	int data;
	
    if(!isEmpty()) {
		data = stack[top];
		stack[top] = 0;// Reset value of stack[top]
		top = top - 1;   
		return data;
    } else {
      printf("Could not retrieve data, Stack is empty.\n");
	  return NULL;
    }
}

void push(int data) {
    if(!isFull()) {
        top = top + 1;   
        stack[top] = data;
    } else {
        printf("Could not insert data, Stack is full.\n");
    }
}