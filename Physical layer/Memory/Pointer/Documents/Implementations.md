# Change value of variable by pointer in a function

```c
#include <stdio.h>

int add (int number);

main () {
	int number = 6;
	add(number);
	printf("%d \n", number);//6
	printf("add(number): %d \n", add(number));//add(number): 7 
}

int add(int number){
	number = number + 1;
	return number;
}
```

The operation above is called **pass by value**. What is sent to the function ``add(number)`` is the value of variable ``number`` ( = 6), not variable ``number``, the variable ``number`` in ``add()`` is just the clone of the genuine variable ``number``. So the value of number still remains unchanged.

**Note**: The problem with change value happen not only with primitive data type like ``int``, ``float``,... but also happen which data structure as data type like ``struct``. Check [Pass by value and pass by reference with struct pointer](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/struct/struct%20pointer.md#pass-by-value-and-pass-by-reference-with-struct-pointer).

## Problem solved

### Using pass by reference

```c
#include <stdio.h>

int add (int *number);

main () {
 int number = 6;
 add(&number);
 printf("%d", number);//7
}

int add(int *number){
	*number = *number + 1;
	return *number;
}
```

### Assign pointer to variable

```c
#include <stdio.h>

int number = 9;
int *pointer = &number;

int add(int *number);

main () {
    add(pointer);
    printf("%d", number); //10
}

int add(int *number){
	*number = *number + 1;
	return *number;
}
```

# Change value of a variable with pointer

Change both local or global variable by using pointer
```cpp
int value = 10;
printf("before %d \n", value); //10
int *ptr = &value;
*ptr = 90;
printf("after %d \n", value); //90
```

Changing the value of local or global ``const`` variable.

```cpp
int main(){
	const int value = 32;
	int *ptr = &value;
	*ptr = 0;
}
```
This program gives warning on ``GCC`` (but ``value`` can still be changed from ``32`` to ``0``)

```
warning: initialization discards ‘const’ qualifier from pointer target type [-Wdiscarded-qualifiers]
     int *ptr = &value;
```
This program gives error on ``G++``:

```
error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]
   int *ptr = &value;
```

Then do optimization in the above program: ``gcc -O test.c`` (same for ``-O1``, ``-O2``, ``-O3``), the warning and result still be like compiling with ``gcc test.c``. Notice that those compilation process are executed on Ubuntu 16.04.

**Problem solved**: Use ``(int*)`` and [volatile](https://github.com/TranPhucVinh/C/blob/master/Introduction/Keywords/volatile.md)

```c
volatile const int value = 32;
int *ptr = (int*)&value;
*ptr = 0;
```

# Change value of a string by function using pointer

Check: ``Example 2 Change value of a string by function using pointer`` in ``Introduction/Data structure/String/Examples part 1.md``.

# Swapping value in a function

```c
#include <stdio.h>
int a, b;
void swap(int *change1, int *change2);
main() {
	printf("Enter the 2 numbers: ");
	scanf ("%d", &a);
	scanf("%d", &b);
	printf("Values of a and b are %d %d \n", a, b);
	swap(&a, &b);
	printf("Values of a and b now are %d %d \n", a, b);
}

void swap(int *change1, int *change2){
	int temp;
	temp = *change1;
	*change1= *change2;
	*change2 = temp;
}
```
```
Enter the 2 numbers: 4
6
Values of a and b are 4 6 
Values of a and b now are 6 4 
```

# Get address of a variable then store into a pointer

```c
#include <stdio.h>

int a = 8;
int b = 10;

void foo(int *ptr)
{
	ptr = &a;
}

int main()
{
	int* ptr;
	ptr = &b;
	printf("*ptr: %d", *ptr);//10
	foo(ptr);
	printf("*ptr: %d", *ptr);//10, expected 8
	return 0;
}
```
We expect ``ptr`` to store the address value of ``a`` but ``ptr`` passed to ``foo()`` is the value of ``ptr`` (i.e ``&b``).

**Problem solved**: 

Using recursive pointer:

```c
#include <stdio.h>

int a = 8;
int b = 10;

void foo(int *ptr)
{
	*ptr = (unsigned long int)&a;
}

int main()
{
	int* ptr;
	ptr = &b;
	printf("*ptr: %d\n", *ptr);//10
	foo((int*)&ptr);
	printf("*ptr: %d\n", *ptr);//10, expected 8
	return 0;
}
```

Using ``memcpy()``

```c
#include <stdio.h>
#include <string.h>

int a = 8;
int b = 10;

void foo(int *ptr)
{
	memcpy(ptr, &a, sizeof(int));
}

int main()
{
	int* ptr;
	ptr = &b;
	printf("*ptr: %d", *ptr);//10
	foo(ptr);
	printf("*ptr: %d", *ptr);//8
	return 0;
}
```

Use a variable to store the address of other variable then changes that variable value

```c
#include <stdio.h>

int a = 8;
int b = 10;

void foo(unsigned long int* pon)
{
	*pon = (unsigned long int)&a;
}

int main()
{
	unsigned long int ptr;
	ptr = (unsigned long int)&b;

	//To view the value mapped by ptr before changing the function
	int* ptr_b;
    ptr_b = &b;
	printf("*ptr: %d\n", *ptr_b);//10

	foo(&ptr);

	//To view the value mapped by ptr after changing the function
    int expect_a = *(int*)(ptr);
	printf("*ptr: %d\n", expect_a);//8
	return 0;
}
```

# Get value of pointer

Can't change the pointing address of pointer when pointer is a function argument

```c
#include <stdio.h>

int number1 = 9;
int number2 = 90;
int *pointer = &number1;

void changeValue (int *pptr);

int main () {
    printf("*pointer before %d \n", *pointer);
    changeValue(pointer);
    printf("*pointer after %d \n", *pointer);
}

void changeValue (int *pptr){
    pptr = &number2; //change pointing address of the argument pointer
}
```
**Output**
```
*pointer before 9
pointer after 9
```

**Problem solved**

```c
void changeValue (int *pptr){
    *pptr = number2;
}
```
**Output**
```
*pointer before 9
*pointer after 90
```
