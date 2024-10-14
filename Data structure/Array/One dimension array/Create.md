# Create array on stack memory
## Create array on stack memory and manually enter the value for each array member

```c
#include <stdio.h>

void set_value_for_array(int *array, int n){
	for (int i=0;i<n;i++){
		printf("Enter value array[%d]:",i );
		scanf("%d", &array[i]);
	}
}
void main() {
	int n;
	printf("enter number n:");
	scanf("%d", &n);
	int array[n];
	set_value_for_array(array, n);

	for (int i=0; i < n; i++){
		printf("Value of member %d is %d \n", i, array[i]);
	}
}
```

## Setup array value at specific index during initialization

```c
int array[6] = {
//Don't need to follow the count up ordered, i.e 1 2 3 4 ...
    [0] = 0,
    [2] = 2,
    [4] = 4,
    [1] = 1,
    [3] = 3,
    [5] = 5
};
```
## Copy an array to another one by memcpy()
```c
int array[3];
int _array[] = {1, 2, 3};
memcpy(array, _array, sizeof(_array));
```
# Create array on heap memory
Use [Dynamic memory allocation](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/API.md) with **stdlib** to create an array **on heap memory**.

# Must not dynamically assign array size

**Must not enter array size**:

```c
// Must not do this
int n, array[n];
printf("Enter the number of members: ");
scanf("%d", &n);

//Segment fault in those lines
for (int i = 0; i < n; i++){    
    array[i] = i;
}
```

Result

```
Segmentation fault (core dumped)
```

Array size must not be declared by a variable **in GCC**

```c
int b = 2;
int array[b] = {1, 2};
```

Or

```c
const int b = 2;
int array[b] = {1, 2};
```

Compiled in GCC gives error: **error: variable-sized object may not be initialized**

But this compiled normally on G++ without warning.

Problem solved for GCC:

```c
int b = 2;//or const int b =2
int array[b];
array[0] = 1;
array[1] = 2;
```

# Fail in static array with size as variable

```c
int a = 9;
static int array[a];
```
Error on both GCC and G++: ``A variable length array cannot have static storage duration``

Problem solved for G++: Use ``const``

```cpp
const int a = 9;
static int array[a];
```
(Using ``const`` for this program still results in the same error)
# Variable-length array
A **variable-length array**, also called **variable-sized** or **runtime-sized**, is an array data structure whose length is determined at run time (instead of at compile time)
```c
void array(int n)
{
    int value[n];
    for (int i = 0; i < n; ++i) value[i]=i;
    for (int i = 0; i < n; ++i) printf("%d ", value[i]);
    printf("\n");
    return;
}

int main(){
    array(10);
}
```
