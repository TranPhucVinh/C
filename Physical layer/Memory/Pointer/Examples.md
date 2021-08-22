### Example 1

Change value of variable by pointer in a function

```c
#include <stdio.h>

int add (int number);

main () {
 int number = 6;
 add(number);
 printf("%d \n", number);
 printf("the return value of the function is %d \n", add(number));
}

int add(int number){
	number = number + 1;
	return number;
}
```
**Result** 
```
6 
the return value of the function is 7 
```

What is sent to the function ``add(number)`` is the value of variable ``number`` ( = 6), not variable ``number``, the variable ``number`` in ``add()`` is just the clone of the genuine variale ``number``. So the value of number still remain unchanged.

**Problem solved**

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

### Example 1.2

Change value of a string by function using pointer.

Check: ``Change value of a string by function using pointer`` in ``Introduction/Data type/String/Char for String.md``.

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

### Example 2: swapping value

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