# Declare pointer

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

## Address of function

```c
void displayString(){
	printf("Hello, World !\n");
}

int main(int argc, char *argv[]) {
	printf("%d\n", displayString);//Has same value with  &displayString
	printf("%d\n", &displayString);//Has same value with displayString
}	
```

# Size of the pointer variable

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

# Get value of pointer

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

# Set value for pointer

Set value for a variable by pointer:

```c
int number;
int *pointer = &number;
*pointer = 190;
printf("number: %d\n", number);//190
```

## Must not directly set value for a pointer deferencing (i.e *pointer)

Based on pointer concept, a pointer store value of another variable so directly setting the value for its deferencing is a useless act and result in **Segmentation fault**
 
```c
//Must not do this as it result in segmentation fault
int *p = 9;//Segmentation fault
```

## Must not arbitrarily set value at specific register address

E.g: Set value at register address ``6295624``

```c
#include <stdio.h>

int *ptr;

int main() 
{
	ptr = (int *)6295624; 
	*ptr = 12;
	printf("*ptr: %d", *ptr);//12
	return 0;
}
```

**Note**: The compiler for that program to work properly is a pure ANSI compiler. For GCC, register address can't be set abritrarily. To work with the program above with the address like ``6295624``, the address ``6295624`` must be the GCC allowable address. User must find the allowable address first with ``&`` for a dummy variable. E.g:

```c
int dummy_variable;
printf("%d", &pdummy_variable);//print out the address of dummy_variable first to find the allowable address
```