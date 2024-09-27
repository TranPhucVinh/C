# Change value of variable by pointer in a function

```c
#include <stdio.h>

int add (int number);

main () {
	int number = 6;
	add(number);
	printf("%d \n", number);//6
	printf("add(number): %d \n", add(number));//add(number): 7 
}

int add(int number){
	number = number + 1;
	return number;
}
```

The operation above is called **pass by value**. What is sent to the function ``add(number)`` is the value of variable ``number`` ( = 6), not variable ``number``, the variable ``number`` in ``add()`` is just the clone of the genuine variable ``number``. So the value of number still remains unchanged.

**Note**: The problem with change value happen not only with primitive data type like ``int``, ``float``,... but also happen which data structure as data type like ``struct``. Check [Pass by value and pass by reference with struct pointer](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/struct/struct%20pointer.md#pass-by-value-and-pass-by-reference-with-struct-pointer).

## Problem solved

### Using pass by reference

```c
#include <stdio.h>

int add (int *number);

main () {
 int number = 6;
 add(&number);
 printf("%d", number);//7
}

int add(int *number){
	*number = *number + 1;
	return *number;
}
```

### Assign pointer to variable

```c
#include <stdio.h>

int number = 9;
int *pointer = &number;

int add(int *number);

main () {
    add(pointer);
    printf("%d", number); //10
}

int add(int *number){
	*number = *number + 1;
	return *number;
}
```
