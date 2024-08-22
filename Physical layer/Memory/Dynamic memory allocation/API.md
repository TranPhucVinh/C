# malloc()

In library ``stdlib.h``

```c
void *malloc(size_t size)
```

``malloc()`` returns a pointer to the allocated memory. The value is stored in **Heap memory**.

**Size of the variable allocated by malloc() can't be gotten** as there is no portable way to find out the size of a malloc'ed block.

```c
char *str;
str = (char *) malloc(100);
printf("%d \n", sizeof(str)); //8: 8 byte (64-bit) is the length of the register as this is size of the pointer str
```

## malloc() for string

```c
char *str;

str = (char *) malloc(15);
strcpy(str, "Learn malloc");
printf("String: %s \n", str); //Learn malloc
```

## malloc() for int

```c
int *intPointer;

intPointer = (int *) malloc(1);
*intPointer = 12;
    
printf("Int value: %d", *intPointer); //12
```
# Examples

## Create a one dimension int array with malloc()

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

## Create a 2 dimension int array with malloc()

Array:

```
{  
   {0, 1, 2, 3} ,
   {4, 5, 6, 7} ,
   {8, 9, 10, 11}
};
```

### By single operations

**Feature**: This example is intended for comprehensive and easy to understand the 2D array creation on heap memory.

**Program**: [create_2d_array_by_single_operations.c](create_2d_array_by_single_operations.c)

For important notice when defining 2D array with double pointer (``int **int_array = (int**) malloc(ROW_SIZE * sizeof(int*)``), check [double pointer document: Define double pointer on heap memory](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Pointer%20to%20pointer.md#define-double-pointer-on-heap-memory).

### By separated operations

**Features**: Seperate the 2D array implementations by functions:

* ``init_array()``
* ``add_value()``
* ``update_value()``
* ``print_array()``
* ``delete_array()``

This program is intended for functions inheritance for 2D array related applications.

**Program**: [create_2d_array_by_separated_operations.c](create_2d_array_by_separated_operations.c)

## Trying to overflow buffer with malloc()

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

Getting the size of a ``malloc()`` string with ``strlen()`` right after it is dynammically allocated **is wrong**.

E.g:

```c
str = (char *) malloc(15);
printf("size %d \n", strlen(str)); //0
```

After setting value:

```c
str = (char *) malloc(15);
strcpy(str, "Learn malloc");
printf("size %d \n", strlen(str)); //12
```

# free()
``free()`` will deallocated the allocated dynamic memory region
```c
int *intPointer;

intPointer = (int *) malloc(1);
*intPointer = 12;
    
printf("Int value before: %d \n", *intPointer); //12
free(intPointer);
printf("Int value after: %d \n", *intPointer); //0
```
Assign value to the deallocated pointer result in unexpected behavior:
```c
intPointer = (int *) malloc(1);
*intPointer = 12;
    
printf("Int value before: %d \n", *intPointer); //12
free(intPointer);
printf("Int value after: %d \n", *intPointer); //0
*intPointer = 134;// Assign value to the deallocated pointer result in unexpected behavior
// This is the result when running on WSL 20.04 and Xilinx Linux 5.15 board
printf("Int value after: %d \n", *intPointer); //134
```
# calloc()

Dynamic allocating a region of memory like ``malloc()`` then set ``NULL`` value to all member inside that memory block. calloc() is corresponded to [kzalloc() in Kernel space](https://github.com/TranPhucVinh/C/tree/master/Kernel/Dynamic%20allocation#kzalloc).

```c
void *calloc(size_t nitems, size_t size)
```

E.g: This will result in the empty/NULL ``str`` variable instead of garbage variable like allocating with ``malloc()``

```c
char *str;

str = (char *) calloc(15, sizeof(char));
printf("String: %s \n", str); //String: 
```

Using ``calloc()`` will takes more time than using ``malloc()`` as it needs time to set NULL value to all member of the block. However it is safer to use ``calloc()`` as it will avoid the issue related to garbage value when using ``malloc()``

# realloc()

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
