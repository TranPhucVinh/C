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
