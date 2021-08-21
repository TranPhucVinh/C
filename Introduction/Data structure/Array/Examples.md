### Example 1

Array as an argument of a function
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