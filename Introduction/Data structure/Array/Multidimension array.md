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

Check ``Dynamic memory allocation.md`` in ``Physical layer/Memory``: ``Example 2: Create a 2 dimension int array with malloc()``.

### 2D array as a function parameter

With ``array[row][column]``:

```c
#include <stdio.h>

#define row 	2
#define column 	3

void twoDimensionArray(int array[row][column]);

int array[row][column] = 
{
	{1, 2, 3},
	{4, 5, 6}
};

int main()
{  
	twoDimensionArray(array);
}

void twoDimensionArray(int array[row][column]){
	printf("%d\n", array[1][2]);//6
}
```
With ``array[][column]``:
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