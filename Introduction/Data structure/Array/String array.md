**Example 1**: Read value from a string array

```c
#include <stdio.h>

char ch_arr[3][10] = {"string 1", "string 2", "string 3"};

main() {
	for (int i=0; i < 3; i++){
		printf("char[%i]: %s \n", i, ch_arr[i]);
	}
}
```

Index of the string can be handled by this way:

```c
printf("char[%i][10]: %s \n", i, ch_arr + i);
```

**Example 2**: Set and read value from a string array

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