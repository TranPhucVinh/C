**Example 1**: Read value from a string array

```c
#include <stdio.h>

char ch_arr[3][10] = {"string 1", "string 2", "string 3"};

main() {
	for (int i=0; i < 3; i++){
		printf("char[%i][10]: %s \n", i, ch_arr[i]);
	}
}
```

Index of the string can be handled by this way:

```c
printf("char[%i][10]: %s \n", i, ch_arr + i);
```