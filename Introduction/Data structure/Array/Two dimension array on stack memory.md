# Create

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

Get column size: ``sizeof(array[0])/sizeof(array[0][0])``

## Create a 2D array and read all of its members

```c
#include <stdio.h>

int row, column;

void set_value_for_row(int _array[row][column], int row, int column){
	for (int i=0; i<column; i++){
		printf("array[%d][%d]:", row, i);
		scanf("%d", &_array[row][i]);
	}
}

void main() {
	printf("enter row number:");
	scanf("%d", &row);
	printf("enter column number:");
	scanf("%d", &column);

	int array[row][column];
	for (int _row = 0; _row < row; _row++){
		set_value_for_row(array, _row, column);
	}
	
	for (int _row = 0; _row < row; _row++){
		for (int _column = 0; _column < column; _column++) printf("array[%d][%d]: %d\n", _row, _column, array[_row][_column]);
	}
}
```

## Set and read value for a string array on stack memory

```c
#include <stdio.h>

#define MEMBER      3
#define STRING_SIZE 20

char ch_arr[MEMBER][STRING_SIZE];

main() {
   for (int i=0; i < MEMBER; i++){
      strcpy(ch_arr[i], "Hello, World !");
   }
	for (int i=0; i < MEMBER; i++){
		printf("char[%i]: %s \n", i, ch_arr[i]);
	}
}
```

**Notice**: ``STRING_SIZE`` must be big enough to store the read string from array, if its size is not enough, there will be overflow error.

```c
#define STRING_SIZE 10
```

The result will be: (overflow)

```
char[0]: Hello, WorHello, WorHello, World ! 
char[1]: Hello, WorHello, World ! 
char[2]: Hello, World ! 
```

# Read

## Read value from a string array

```c
#include <stdio.h>

char string_array[3][10] = {"string 1", "string 2", "string 3"};

int main() {
	for (int i=0; i < 3; i++){
		printf("string_array[%i]: %s \n", i, string_array[i]);
	}
}
```

Index of the string can be handled by this way:

```c
printf("string_array[%i]: %s \n", i, string_array + i);
```

To get a character inside the string: 

```c
printf("string_array[0][1]: %c \n", string_array[0][1]); //t
```

## Read value from a 2 dimension array

Read from ``row`` and ``column`` with:

* ``array[row][column]``
* ``(*(array+row))[column]``
* ``*(*(array+row))+column``

# 2D array on stack memory as a function parameter

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

Accessing 2D array member with index from a pointer of pointer array like this gives ``Segment fault``

```c
void intArray(int **array){
	printf("array[0][1]: %d\n", array[0][1]);
}

int int_array[ROW_SIZE][COLUMN_SIZE] = {{1, 2, 3}, {4, 5, 6}};

intArray((int**)int_array);
```

That happens as arrays decay into pointers once, it doesn't happen recursively. An array of arrays decays into a pointer to an array, not into a pointer to a pointer.

So a 2 dimension array declared by pointer to pointer can be passed into functions, check [2D array as a function parameter in Two dimension array on heap memory](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/Array/Two%20dimension%20array%20on%20heap%20memory.md#2d-array-as-a-function-parameter)
