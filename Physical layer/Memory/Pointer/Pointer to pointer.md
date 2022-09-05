Pointer to pointer is also known as double pointer.

### Create

```c
#include <stdio.h>

int number = 9;

int *pointer = &number;
int **double_pointer = &pointer;

int main(){
	printf("*pointer: %d \n", *pointer);//9
	printf("Address of pointer: %p \n", &pointer);//0x601040
	printf("double_pointer: %p \n", double_pointer);//0x601040
	printf("**double_pointer: %d \n", **double_pointer);//9
}
```

### Applications

* [Two dimension array on heap memory](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/Array/Two%20dimension%20array%20on%20stack%20memory.md)
* [Thread creation: Get return from a thread and store to a variable]([https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#example-1](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#get-return-from-a-thread-and-store-to-a-variable)
