#include <stdio.h> 
#include <stdlib.h> 

#define STACK_SIZE 100
  
int stack[STACK_SIZE];
int top = -1;      

int     is_empty();
int     is_full();   
void    pop();
void    push(int data);
int     get_top();
int     get_size();

int main() { 
    // int array[] = {5,2,13,3,8};
    int array[] = {1, 1, 1, 1};
    int sz = sizeof(array)/sizeof(int);

    for (int i = 0; i < sz; i++) {
        if (is_empty()) push(array[i]);
        else {
            while (!is_empty() && (array[i] > get_top()) )  {
                pop();
            }
            push(array[i]);
        }
    }

    for (int i = 0; i < get_size(); i++) {
        printf("%d ", stack[i]);
    }
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

int get_size() {
    return top + 1;
}
