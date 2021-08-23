``new`` and ``delete`` keywords are only available in ``G++`` and is not available in ``GCC``.

### new

```c
#include <stdio.h>

int main()
{  
	int *int_number = new int;
	int *int_array = new int[2];
	*int_number = 12;
	int_array[0] = 1;
	int_array[1] = 2;
	printf("int_number: %d\n", *int_number); //12
	printf("int_array[1]: %d\n", int_array[1]); //2
}
```
Or can define:

```c
int *int_number;
int_number = new int;
*int_number = 23;
```

### delete

```c
int *int_number = new int;
*int_number = 12;
printf("int_number: %d\n", *int_number); //12
delete int_number;
printf("int_number: %d\n", *int_number); //0
```
Or can use:
```c
delete[] int_number;
```