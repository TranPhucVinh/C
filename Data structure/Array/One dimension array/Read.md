# Read array member at index

Read from ``index`` with:

* ``array[index]``
* ``*(array + index)``
# Get size of an array

```c
int array[] = {1, 2, 3};
int data[3];
sizeof(array);//12
sizeof(data);
size_t arraySize = sizeof(array)/sizeof(array[0]);//3
size_t dataSize = sizeof(array)/sizeof(array[0]);//3
```
Or
```c
size_t arraySize = sizeof(array)/sizeof(int);
```

Using this method is only right when you are dealing with **arrays not received as function parameters**. An array sent as a parameter to a function is treated as a pointer, so sizeof will return the pointer's size, instead of the array's. The only way to get the size of the array in this case is to **passing its size as an argument to the function**.

However, for the non-zero member array, we can get its size by this way:

```c
void intArray(int *array);
int array[] = {1, 2, 3};

int main() {  
	intArray(array);
}

void intArray(int *array){
    int size = 0;
    while (array[size] != 0) size++;

	for (int i = 0; i < size; i++){
		printf("array[%d]: %d\n", i, array[i]);
	}
}
```

Same with non-NULL string:

```c
char *displayed_string = "Hello, World !";

int get_string_size(char *string)
{
    int size = 0;
    while (string[size] != 0) ++size;
    return size;
}

printf("String size %d\n", get_string_size(displayed_string));//String size: 14
```

# Find min number in an array

```c
#include <stdio.h>

void main() {
	int array[5] = {5, 1, 3, 6, 2};

    int min = array[0];
    for (int i=1; i < n; i++){
        if (min >= array[i]) min = array[i];
	}
    printf("min: %d\n", min);
}
```