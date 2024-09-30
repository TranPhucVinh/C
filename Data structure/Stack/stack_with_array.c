#include <stdio.h>

#define STACK_SIZE 8
  
int stack[STACK_SIZE];
int top = -1;            

int     is_empty();
int     is_full();   
void    pop();
void    push(int data);
int     get_top();

int main() {
	// push items into the stack 
	push(3);
	push(5);
	push(9);
	push(1);
	push(12);
	push(15);

    // print stack data by getting the top then pop it out
    while(!is_empty()) {
        int data = get_top();
        printf("%d ", data);
        pop();
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

void pop() {	
    if(!is_empty()) {
		stack[top] = 0;// Reset value of stack[top]
		top = top - 1;   
    } else {
      printf("Could not retrieve data. Stack is empty.\n");
    }
    return;
}

void push(int data) {
    if(!is_full()) {
        top = top + 1;   
        stack[top] = data;
    } else {
        printf("Could not insert data, Stack is full.\n");
    }
}

int get_top() {
    if (top != -1) return stack[top];
    else {
        printf("Stack is empty\n");
        return -1;
    }
}
