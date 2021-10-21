## Example 1

Change value of variable by pointer in a function

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

The operation above is called **pass by value**. What is sent to the function ``add(number)`` is the value of variable ``number`` ( = 6), not variable ``number``, the variable ``number`` in ``add()`` is just the clone of the genuine variale ``number``. So the value of number still remain unchanged.

**Problem solved**: Using pass by reference

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

### Example 1.1: Pointer assign to variable

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

### An example of passing by value

Get address of a variable then store into a pointer.

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

**Problem solved**: Using ``memcpy()``

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

### Example 1.2

Change value of a string by function using pointer.

Check: ``Example 2 Change value of a string by function using pointer`` in ``Introduction/Data structure/String/Examples part 1.md``.

### Example 1.3: Change value of a variable with pointer

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
This program gives warning on ``GCC``:

```
warning: initialization discards ‘const’ qualifier from pointer target type [-Wdiscarded-qualifiers]
     int *ptr = &value;
```
This program gives error on ``G++``:

```
error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]
   int *ptr = &value;
```
**Problem solved**: Use ``(int*)`` and ``volatile``

```c
volatile const int value = 32;
int *ptr = (int*)&value;
*ptr = 0;
```

## Example 2

Swapping value

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

### Get value of pointer

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
