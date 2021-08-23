### Create a 2 dimension array on stack memory

```c
int a[3][4] = {  
   {0, 1, 2, 3} ,   /*  initializers for row indexed by 0 */
   {4, 5, 6, 7} ,   /*  initializers for row indexed by 1 */
   {8, 9, 10, 11}   /*  initializers for row indexed by 2 */
};

printf("%d: ", a[2][3]); //11
```
The missing value when the array size is smaller than the row or column size is set by ``0``.

```c
int a[3][4] = {  
   {0, 1, 2} ,
   {4, 7} ,
   {8, 9, 10, 11}
};

printf("%d", a[0][3]); //0
```

Multidimension array is can be defined simply by ``{}`` as ``GCC`` and ``G++`` consider multidimension array as a one dimension array.

```c
#define row 	2
#define column 	3

int array[row][column] = {1, 2, 3, 4, 5, 6};

printf("array[%d][%d]: %d", 0, 1, array[1][1]);//5
printf("array[%d][%d]: %d", 0, 1, array[1][2]);//6
```

### Create a 2 dimension array on heap memory

For a 2 dimension array with ``row`` and ``column`` on heap memory: Check ``Example 2: Create a 2 dimension int array with malloc()`` in ``Dynamic memory allocation.md`` inside ``Physical layer/Memory``.

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

### Read value from a 2 dimension array

Read from ``row`` and ``column`` with:

* ``array[row][column]``
* ``(*(array+row))[column]``
* ``*(*(array+row))+column``

## 2D array as a function parameter

### Using array[row][column]

```c
#include <stdio.h>

#define ROW_SIZE 		2
#define COLUMN_SIZE 	3

void twoDimensionArray(int array[ROW_SIZE][COLUMN_SIZE]);

int array[ROW_SIZE][COLUMN_SIZE] = 
{
	{1, 2, 3},
	{4, 5, 6}
};

int main()
{  
	twoDimensionArray(array);
}

void twoDimensionArray(int array[ROW_SIZE][COLUMN_SIZE]){
	printf("%d\n", array[1][2]);//6
}
```
### Using array[][column]

```c
#include <stdio.h>

#define ROW_SIZE 		2
#define COLUMN_SIZE 	3

void twoDimensionArray(int array[][COLUMN_SIZE], int rowSize);

int array[ROW_SIZE][COLUMN_SIZE] = 
{
	{1, 2, 3},
	{4, 5, 6}
};

int main()
{  
	twoDimensionArray(array, ROW_SIZE);
}

void twoDimensionArray(int array[][COLUMN_SIZE], int rowSize){
	for (int column = 0; column < COLUMN_SIZE; column++){
		for (int row = 0; row < ROW_SIZE; row++) printf("array[%d][%d]: %d\n", row, column, array[row][column]);
	}
}
```
### Using pointer

```c
#include <stdio.h>

#define ROW_SIZE 	2
#define COLUMN_SIZE 	3

void twoDimensionArray(int *array, int row, int column);

int array[ROW_SIZE][COLUMN_SIZE] = 
{
	{1, 2, 3},
	{4, 5, 6}
};

int main()
{  
	twoDimensionArray((int*)array, ROW_SIZE, COLUMN_SIZE);
}

void twoDimensionArray(int *array, int row, int column){
	for (int row = 0; row < ROW_SIZE; row++){
		for (int column = 0; column < COLUMN_SIZE; column++) printf("array[%d][%d]: %d\n", row, column, (array+row*COLUMN_SIZE)[column]);
	}
}
```
### Can't use pointer of pointer

This function declaration gives ``Segment fault``

```c
void intArray(int **array){
	printf("array[0][1]: %d\n", array[0][1]);
}

int int_array[ROW_SIZE][COLUMN_SIZE] = {{1, 2, 3}, {4, 5, 6}};

intArray((int**)int_array);
```

That happens as arrays decay into pointers once, it doesn't happen recursively. An array of arrays decays into a pointer to an array, not into a pointer to a pointer.

So a 2 dimension array declared by pointer to pointer can be passed into functions:

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

	intArray((int**)int_array);
}

void intArray(int **array){
	printf("array[1][2] %d\n", array[1][2]);
}
```