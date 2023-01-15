Build stack with array

```c
#include <stdio.h>

#define stackSize 8
  
int stack[stackSize];
int top = -1;            

int isempty();
int isfull();   
int pop();
int push(int data);

int main() {
   // push items on to the stack 
   push(3);
   push(5);
   push(9);
   push(1);
   push(12);
   push(15);

   // print stack data 
   while(!isempty()) {
      int data = pop();
      printf("%d ",data);
   }
  printf("\n");
   printf("Stack full: %s\n" , isfull()?"true":"false");
   printf("Stack empty: %s\n" , isempty()?"true":"false");
   
   return 0;
}

int isempty() {
   if(top == -1)
      return 1;
   else
      return 0;
}

int isfull() {
   if(top == stackSize)
      return 1;
   else
      return 0;
}

int pop() {
   int data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

int push(int data) {
   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}
```
