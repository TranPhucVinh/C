In computer science, a **reference** is a value that enables a program to indirectly access a particular ``datum``, such as a variable's value or a record, in the computer's memory or in some other storage device. **Pointers** are the most primitive type of reference.

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
const char *displayedString = "Hello, World !";//String pointer declaration
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
return(0);
```

**Note**: ``*&a`` is ``a``.

Set value for a variable by pointer:

```c
int number;
int *pointer = &number;
*pointer = 190;
printf("number: %d\n", number);//190
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