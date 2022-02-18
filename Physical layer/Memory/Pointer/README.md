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

### Types of pointer

Check ![types of pointer document]()

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