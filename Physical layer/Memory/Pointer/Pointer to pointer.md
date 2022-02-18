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

Other way to define:

```c
#include <stdio.h>

int number = 9;

int *pointer = &number;
int **double_pointer;

int main(){
	double_pointer = &pointer;
	printf("*pointer: %d \n", *pointer);//9
	printf("Address of pointer: %p \n", &pointer);//0x601040
	printf("double_pointer: %p \n", double_pointer);//0x601040
	printf("**double_pointer: %d \n", **double_pointer);//9
}
```

If define:

```c
int number = 9;

int *pointer = &number;
int **double_pointer;
double_pointer = &pointer;

int main(){
	//Operations go here
}
```

There will be error:

```
test.c:7:1: warning: type defaults to ‘int’ in declaration of ‘double_pointer’ [-Wimplicit-int]
test.c:7:1: error: conflicting types for ‘double_pointer’
test.c:6:7: note: previous declaration of ‘double_pointer’ was here
 int **double_pointer;
       ^
test.c:7:18: warning: initialization makes integer from pointer without a cast [-Wint-conversion]
 double_pointer = &pointer;
                  ^
test.c:7:18: error: initializer element is not computable at load time
```

### Applications

* [Array of pointer](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/Array/Array%20of%20pointer.md)
* [Create a 2 dimension int array with malloc()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory/Using%20stdlib.md)
* [Thread creation: Get return from a thread and store to a variable](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#example-1)
