In computer science, a **reference** is a value that enables a program to indirectly access a particular ``datum``, such as a variable's value or a record, in the computer's memory or in some other storage device. **Pointers** are the most primitive type of reference.

The parameter to a function can be a copy of a value that is represented by variable, which is known as **pass by value**, or can be a reference to a memory space that stores value of variable, which is known as **pass by reference**.

A pointer is a variable that stores address of other variable. All the pointer syntax works identically in both C/C++.

* ``*p``: declare a pointer
* ``*p``: value at address
* ``&``: get the address of the variable
* ``%p``: is used to print out the address as it can print out the hex value.

## Declare pointer variable

```c
int *intPointer; //pointer to integer
``` 

Or it can be

```c
int* intPointer;
```

```c
char *p0; //pointer to character
double *p1; // pointer to double
```

C program doesn't support reference as function argument:

```c
//THAT IS NOT SUPPORTED FOR A C PROGRAM
int a = 8;

void foo(uintptr_t &object_ptr)
{
	object_ptr = (uintptr_t)&a;
}
```

### Get value of pointer

```c
int *p;
int a = 9;
p = &a; //variable p now stores the address of variable a
int *pointer = &a; //variable pointer now stores the address of variable a
printf("pointer value %p \n", p); //0x601030
printf("address value of variable a %p \n", &a); //0x601030
printf("address of pointer variable %p \n", &p); //0x601048
printf("Value of variable pointer %p \n", pointer); //0x601030
printf("variable value %d \n", *p); //9
printf("*& value is %d \n", *&a); //9
printf("Value *pointer is %d \n", *pointer); //9
```

**Note**: ``*&a`` is ``a``.

Set value for a variable by pointer:

```c
int number;
int *pointer = &number;
*pointer = 190;
printf("number: %d\n", number);//190
```

Address of function:

```c
void displayString(){
	printf("Hello, World !\n");
}

int main(int argc, char *argv[]) {
	printf("%d\n", displayString);//Has same value with  &displayString
	printf("%d\n", &displayString);//Has same value with displayString
}	
```

### Wrong declaration and operation that must be avoided

```c
int *number = 12;
printf("*number: %d", *number);//Segmentation fault (core dumped)
printf("number: %d", number);//12
```

This gives compilation error in G++:

```
error: invalid conversion from ‘int’ to ‘int*’ [-fpermissive]
  int *number = 12;
```

But this define gives warning in GCC and has the result:

```c
printf("*number: %d", *number);//Segmentation fault (core dumped)
printf("number: %d", number);//12
```

``number: 12`` is totally wrong as ``number`` is expected to store the address.

**Note**: Except string pointer declarion (``char *displayedString = "Hello, World !"``), you musn't set the value to the pointer variable when defining them:

```c
int *number = 12;//Must not do it
```

The same error with multidimension array:

```c
int **int_array = {{1, 2, 3}, {4, 5, 6}};//Must not do it
```
**Error**

```
error: scalar object ‘int_array’ requires one element in initializer
```

To work with ``int *number`` and ``int **int_array``, check ``Dynamic memory allocation.md`` in ``Physical layer/Memory/``.

### sizeof()

In 64-bit computer

```c
int a;
sizeof(&a); //8
```

```c
char *test = "1";
printf("%d", sizeof(test)); //8
```

``sizeof(&a)`` and ``sizeof(test)`` are 8 byte they store the 64-bit address.

To get size of a string point by ``char*``, use ``strlen()``

```c
char *test = "123";
strlen(test)); //3
```

## const pointer

String declaration with pointer is highly recommended to use ``const char*``:

```c
const char *displayedString = "Hello, World !";
```

``const`` pointer for other variable

```c
/*
	int const* pointer or const int* pointer will give the same result
*/
const int *pointer;

int a = 10, b = 20;
pointer = &a;
printf("pointer: %d\n", *pointer);//10
a = 19;
printf("pointer: %d\n", *pointer);//19
pointer = &b;
printf("pointer: %d\n", *pointer);//20
```

Declaration way effect the way to get and set value of const pointer, using ``const int *pointer`` like above will have the different way to get and set the value of from ``int* const pointer``

Compilation error in ``GCC`` and ``G++``:

```c
int a = 2, b = 10;
int* const pointer;
pointer = &a;//This give compilation error in GCC
```
Set value for ``int* const pointer``:
```c
int a = 2, b = 10;
int* const pointer = &a;
printf("%d\n", *pointer);//2

//Setting pointer to other address now give compilation error in GCC and G++
//pointer = &b;
```
