### malloc()

In library ``stdlib.h``

```c
void *malloc(size_t size)
```

``malloc()`` returns a pointer to the allocated memory. The value is stored in **Heap memory**.

Size of the variable allocated by ``malloc()`` can't be get as there is no portable way to find out the size of a malloc'ed block.

**String**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "Learn malloc");
   printf("String: %s \n", str); //Learn malloc
}   
```

**Int**

```c
int *intPointer;

intPointer = (int *) malloc(1);
*intPointer = 12;
    
printf("Int value: %d", *intPointer); //12
```

**Example 1**: Create a one dimension int array with ``malloc()``

```c
#define arraySize 3

int main(){
   int* intArray = (int*) malloc (arraySize * sizeof(int));

   for (int i = 0; i < arraySize; i++){
      intArray[i] = i;
   }
   for (int i = 0; i < arraySize; i++){
      printf("intArray[%d]: %d\n", i, intArray[i]);
   }
}
```

**Example 2**: Create a 2 dimension int array with ``malloc()``

Array:

```
{  
   {0, 1, 2} ,
   {3, 4, 5} ,
   {6, 7, 8}
};
```

```c
#include <stdio.h>
#include <stdlib.h>

#define rowSize 3
#define columnSize 3

int main(){
	int **int_array = (int**) malloc(columnSize * sizeof(int*));

	for (int row = 0; row < rowSize; row++){
		int_array[row] = (int*) malloc(columnSize * sizeof(int));
	}

	int index = 0;
	for (int row = 0; row < rowSize; row++){
		for (int column = 0; column < columnSize; column++){
			int_array[row][column] = index;
			index += 1;
		}	
	}
}
```

### Trying to overflow buffer with malloc()

```c
char *str;
int *intPointer;

str = (char *) malloc(1);
strcpy(str, "Hello World");
intPointer = (int *) malloc(1);
*intPointer = 1024;

printf("String: %s \n", str); //Hello World
printf("Int value: %d \n", *intPointer); //1024
```    

Both ``intPointer`` and ``str`` has overflow its allocated memory (1 byte) but the data is not overflow. That is because ``malloc(size)`` returns a location in memory where at least size bytes are available for you to use. You are likely to be able to write data to a string with ``char[]`` like ``displayedString[size]``, but those bytes may belong to other bits of your program, which will cause problems later in the execution.

### free()

```c
int *intPointer;

intPointer = (int *) malloc(1);
*intPointer = 12;
    
printf("Int value before: %d \n", *intPointer); //12
free(intPointer);
printf("Int value after: %d \n", *intPointer); //0
```

### realloc()

``realloc()`` is used to dynamically change the memory allocation of a previously allocated memory.

```c
void *realloc(void *ptr, size_t size); 
```

```c
int* intPointer = (int*) malloc (5 * sizeof(int));
intPointer = ... //A 20 bytes memory block is dynamically allocated to intPointer as an array
intPointer = realloc(intPointer, 10*sizeof(int));
intPointer = ... //The size of intPointer is changed from 20 bytes to 40 bytes dynamically
```