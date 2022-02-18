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

**Note**: Except char pointer as string declarion (``char *displayed_string = "Hello, World !"``), you musn't set the value to the pointer variable when defining them:

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

### Size of the pointer variable.

To get size of the pointer variable, use ``sizeof()``. Size of the pointer variable doesn't depend on its type as it stores the address of other variable and address of a variable has ``int`` type. So size of a pointer variable is ``int``.

In 64-bit computer

```c
int a;
sizeof(&a); //8
```

```c
char *test = "1";
printf("%d", sizeof(test)); //8
```

## Pointer and const

### pointer to const

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

### const pointer

A const pointer doesn't allow the pointer to change the address at later state of the program.

This gives compilation error in ``GCC`` and ``G++``:

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
### Const pointer to a const interger

```c
int const * a const;
```

## NULL pointer

Null pointer actually means a pointer that does not point to any valid location. We define a pointer to be null when we want to make sure that the pointer does not point to any valid location and not to use that pointer to change anything. If we don't use null pointer, then we can't verify whether this pointer points to any valid location or not.

```c
int a = 10;

int main () {
	int *ptr = NULL;
	ptr = &a;
	printf("%d",  *ptr);//10
}   
```

**Error**: If get ``*ptr`` after declaring NULL, there will segment fault error

```c
int a = 10;
int *ptr = NULL;
printf("%d",  *ptr);//Segment fault
ptr = &a;
printf("%d",  *ptr);
```
