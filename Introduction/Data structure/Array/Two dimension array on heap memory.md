## Create

For a 2 dimension array with ``row`` and ``column`` on heap memory: Check [Example 2: Create a 2 dimension int array with malloc()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory/Using%20stdlib.md) in ``Dynamic memory allocation`` inside ``Physical layer/Memory``.

Create a 2 dimension array with ``row`` stored on stack memory and ``column`` stored on heap memory:

```c
#include <stdio.h>
#include <stdlib.h>

#define columnSize 3
#define rowSize 2

int main(){
	int *array[columnSize];

	for (int column = 0; column < columnSize; column++){
		array[column] = (int*) malloc (rowSize * sizeof(int));
	}

	int number = 0;
	for (int row = 0; row < rowSize; row++){
		for (int column = 0; column < columnSize; column++){
			array[row][column] = number;
			number += 1;
		}
	}
}
```

## 2D array as a function parameter

A 2 dimension array declared by pointer to pointer can be passed into functions:

```c
#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 	2
#define COLUMN_SIZE 	3

void intArray(int **array);

int main()
{  
	int **int_array = (int**) malloc(COLUMN_SIZE * sizeof(int*));

	for (int row = 0; row < ROW_SIZE; row++){
		int_array[row] = (int*) malloc(COLUMN_SIZE * sizeof(int));
	}

	int index = 0;
	for (int row = 0; row < ROW_SIZE; row++){
		for (int column = 0; column < COLUMN_SIZE; column++){
			int_array[row][column] = index;
			index += 1;
		}	
	}

	intArray((int**)int_array);//array[1][2] 5
}

void intArray(int **array){
	printf("array[1][2] %d\n", array[1][2]);
}
```
