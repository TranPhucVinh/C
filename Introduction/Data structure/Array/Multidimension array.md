### Multidimensional array

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

## String array

### Define with 2-dimension array

Read value from a string array

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

### Define with char pointer

```c
char *string_array[3] = {"string 1", "string 2", "string 3"};
```

This gives no error in GCC and gives warning in G++:

```
warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
```

```c
#include <stdio.h>

char *string_array[3] = {"string 1", "string 2", "string 3"};

int main() {
	for (int i=0; i < 3; i++){
		printf("string_array[%i]: %s \n", i, string_array[i]);
	}

	//Get value of index 2
	printf("string_array[2]: %s\n", *(string_array + 2));

	//Get a character inside the string: 
	printf("string_array[2][2]: %c\n", (*(string_array + 2))[2]);
}
```

### Example 2

Set and read value from a string array

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