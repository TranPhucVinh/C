# Operations for array

## Create

### On stack memory

* Create array and manually enter the value for each array member: [create_array.c](create_array.c)
* Create new member from index: [create_new_member.c](create_new_member.c)

An array can be created like this:

```c
int array[6] = {
//Don't need to follow the count up ordered, i.e 1 2 3 4 ...
    [0] = 0,
    [2] = 2,
    [4] = 4,
    [1] = 1,
    [3] = 3,
    [5] = 5
};
```

### On heap memory

Check [Dynamic memory allocation](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Memory/Dynamic%20memory%20allocation) with [stdlib](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/Using%20stdlib.md) and [G++](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/Using%20G%2B%2B.md).

## Read

Read from ``index`` with:

* ``array[index]``
* ``*(array + index)``

## Update

* Update value for array member from index: ``array[index] = new_value``

## Delete

* Delete member in array from index: ``delete.c`` 

# Size of an array

```c
int array[] = {1, 2, 3};
int data[3];
sizeof(array);//12
sizeof(data);
size_t arraySize = sizeof(array)/sizeof(array[0]);//3
size_t dataSize = sizeof(array)/sizeof(array[0]);//3
```
Or
```c
size_t arraySize = sizeof(array)/sizeof(int);
```

Using this method is only right when you are dealing with **arrays not received as function parameters**. An array sent as a parameter to a function is treated as a pointer, so sizeof will return the pointer's size, instead of the array's. The only way to get the size of the array in this case is to passing its size as an argument to the function.

Get size of array by function:

```c
int array[] = {1, 2, 3};

int get_array_size(int *array)
{
    int size = 0;
    while (array[size] != 0) ++size;
    return size;
}


printf("Array size: %d\n", get_array_size(array));//Array size: 3
```

For string as char array or char pointer:

```c
char *displayed_string = "Hello, World !";

int get_string_size(char *string)
{
    int size = 0;
    while (string[size] != 0) ++size;
    return size;
}

printf("String size %d\n", get_string_size(displayed_string));//String size: 14
```

## Fail in dynamically assigned the size of array

Enter the size of array

```c
int i, n, array[n];
printf("Enter the number of members: ");
scanf("%d", &n);

//Segment fault in those lines
for (i = 0; i < n; i++){    
   array[i] = i;
}
```

Result

```
Segmentation fault (core dumped)
```

Array size must not be declared by a variable **in GCC**

```c
int b = 2;
int array[b] = {1, 2};
```

Or

```c
const int b = 2;
int array[b] = {1, 2};
```

Compiled in GCC gives:

```
error: variable-sized object may not be initialized
```

But this compiled normally on G++ without warning.

Problem solved for GCC:

```c
int b = 2;//or const int b =2
int array[b];
array[0] = 1;
array[1] = 2;
```

## Fail in static array with size as variable

```c
int a = 9;
static int array[a];
```
Error on both GCC and G++: ``A variable length array cannot have static storage duration``

Problem solved for G++: Use ``const``

```cpp
const int a = 9;
static int array[a];
```
(Using ``const`` for this program still results in the same error)
# Array as an argument of a function

Using array with size

```c
#include <stdio.h>

void intArray(int array[3]);
int array[] = {1, 2, 3};

int main()
{  
	intArray(array);
}

void intArray(int array[3]){
	for (int i = 0; i < 3; i++){
		printf("array[%d]: %d\n", i, array[i]);
	}
}
```

Or can define:

```c
void intArray(int array[], int size);
```

Using array pointer

```c
#include <stdio.h>

void intArray(int *array, int size);
int array[] = {1, 2, 3};

int main()
{  
	int arraySize = sizeof(array)/sizeof(int); 
	intArray(array, arraySize);
}

void intArray(int *array, int size){
	for (int i = 0; i < size; i++){
		printf("array[%d]: %d\n", i, array[i]);
	}
}
```

Change value of an array by a function
```c
void intArray(int *array, int size);
int array[] = {1, 2, 3};

int main()
{  
	int arraySize = sizeof(array)/sizeof(int); 
	intArray(array, arraySize);
}

void intArray(int *array, int size){
	for (int i = 0; i < size; i++){
		array[i] = i+100;
	}
}
```
# Function returns an array

Using stack memory with ``static``:

```c
#include <stdio.h>

int *returnArray();
int main(){
	int *array_pointer;
	array_pointer = returnArray();
	printf("%d\n", array_pointer[1]);//2
}

int *returnArray(){
	static int array[] = {1, 2, 3};
	return array;
}
```

Using heap memory with ``malloc()``:

```c
#include <stdio.h>
#include <stdlib.h>

#define arraySize 3

int *returnArray();
int main(){
	int *array_pointer;
	array_pointer = returnArray();
   	int index = 1;
	printf("array_pointer[%d]: %d\n", index, array_pointer[index]);//1
	printf("Address of array_pointer %p\n", array_pointer);//Has the same address with array inside returnArray()
	free(array_pointer);//Free dynamic memory after using
	printf("array_pointer[%d]: %d\n", index, array_pointer[index]);//0
}

int *returnArray(){
	int *array = (int*) malloc (arraySize * sizeof(int));
	for (int i = 0; i < arraySize; i++){
      array[i] = i;
	}
	printf("Address of array %p\n", array);
	return array;
}
```
