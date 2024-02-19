# Operations for array

## Create

### On stack memory

Create array and manually enter the value for each array member: [create_array.c](create_array.c)

An array can be created like this:

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

**Insert a new member from index**

**Precondition**: Size of the array to be inserted must bigger its total member

E.g 

```c
//Declare array with 100 member to first store 5 member
int array[100] = {1,3,5,7,8};
```

If the array size is fixed with its first total members, there will error later when inserting the new member because the array will then be extended to the unallocated memory location.

E.g

```c
//Declare array with 100 member to first store 5 member
int array[] = {1,3,5,7,8};

array[5] = 10;//Insert a new member at index 5, the unallocated location, result in memory segment fault
```

Program: [create_new_member.c](create_new_member.c)
 
### On heap memory

Check [Dynamic memory allocation](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Memory/Dynamic%20memory%20allocation) with [stdlib](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/Using%20stdlib.md) and [G++](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/Using%20G%2B%2B.md).

## Read

Read from ``index`` with:

* ``array[index]``
* ``*(array + index)``

## Update

* Update value for array member from index: ``array[index] = new_value``

## Delete

* Delete member in array from index: ``delete.c`` 

# Size of an array

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

Using this method is only right when you are dealing with **arrays not received as function parameters**. An array sent as a parameter to a function is treated as a pointer, so sizeof will return the pointer's size, instead of the array's. The only way to get the size of the array in this case is to passing its size as an argument to the function.

Get size of array by function:

```c
int array[] = {1, 2, 3};

int get_array_size(int *array)
{
    int size = 0;
    while (array[size] != 0) ++size;
    return size;
}


printf("Array size: %d\n", get_array_size(array));//Array size: 3
```

For string as char array or char pointer:

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

## Must not dynamically assign array size

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

## Fail in static array with size as variable

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
