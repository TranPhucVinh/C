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

# Change address of a pointer as a function argument

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
