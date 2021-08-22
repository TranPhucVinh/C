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

### Example 1

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