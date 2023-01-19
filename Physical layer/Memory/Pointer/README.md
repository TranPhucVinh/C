In computer science, a **reference** is a value that enables a program to indirectly access a particular ``datum``, such as a variable's value or a record, in the computer's memory or in some other storage device. **Pointers** are the most primitive type of reference.

The parameter to a function can be a copy of a value that is represented by variable, which is known as **pass by value**, or can be a reference to a memory space that stores value of variable, which is known as **pass by reference**.

A pointer is a variable that stores address of other variable. All the pointer syntax works identically in both C/C++.

* ``*p``: declare a pointer
* ``*p``: value at address
* ``&``: get the address of the variable
* ``%p``: is used to print out the address as it can print out the hex value.

Fundamental concepts of pointer includes:

* [Declare pointer](#declare-pointer)
* [Pointer and array](Pointer%20and%20Array.md)
* [Pointer to pointer]() or double pointer
* [Function pointer](Function%20pointer.md)

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

C program doesn't support reference (``uintptr_t``) as function argument like this ``void foo(uintptr_t &object_ptr)``.

**Address of function**

```c
void displayString(){
	printf("Hello, World !\n");
}

int main(int argc, char *argv[]) {
	printf("%d\n", displayString);//Has same value with  &displayString
	printf("%d\n", &displayString);//Has same value with displayString
}	
```

## Size of the pointer variable.

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

## Get value of pointer

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

## Set value with pointer

Set value for a variable by pointer:

```c
int number;
int *pointer = &number;
*pointer = 190;
printf("number: %d\n", number);//190
```

Set value at specific register address:

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

# [Types of pointer](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Types%20of%20pointer.md)

Types of pointer:
* Wild pointer
* [pointer to const](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Types%20of%20pointer.md#pointer-to-const) vs [const pointer](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Types%20of%20pointer.md#const-pointer)
* [NULL pointer](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Types%20of%20pointer.md#null-pointer)
* [Void pointer](Void%20pointer.md)

**Note**: [Type casting pointer](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Types%20of%20pointer.md#type-casting-pointer) from the smaller one to the bigger one and in reverse are different.

# + arithmetic issue

```c
char char_arr[5];
int *int_ptr1, *int_ptr2;
char *char_ptr1, *char_ptr2;

//Set value for all member in array for later access
for(int i = 0; i < 5; i++)
{
    char_arr[i] = i;
}

char_ptr1 = &char_arr[0];
int_ptr1 = (int*)&char_arr[0];

printf("char_ptr1: %p, int_ptr1: %p\n", char_ptr1, int_ptr1);//char_ptr1: 0x7ffebc027653, int_ptr1: 0x7ffebc027653

char_ptr2 = char_ptr1 + 1;
int_ptr2 = int_ptr1 + 1;

printf("char_ptr2: %p, int_ptr2: %p\n", char_ptr2, int_ptr2);//char_ptr2: 0x7ffebc027654, int_ptr2: 0x7ffebc027657
printf("*char_ptr2: %d, *int_ptr2: %d\n", *char_ptr2, *int_ptr2);//*char_ptr2: 1, *int_ptr2: 633339908; *int_ptr2 print out garbage value in this way 
printf("*char_ptr2: %d, *int_ptr2: %d\n", *char_ptr2, (char)*int_ptr2);//*char_ptr2: 1, *int_ptr2: 4
```

In this example, we set ``char_ptr1`` (``char`` type) and ``int_ptr1`` (``int`` type) to have the same address, then increase them by 1 in both ``char_ptr2`` and ``int_ptr2``. With ``1`` from increment, we expect both ``*char_ptr2`` and ``*int_ptr2`` to have the value of ``1`` as they both have the value of ``char_arr[1]``. In fact, just only ``*char_ptr2 = char_arr[1]`` while ``*int_ptr2 = 4``, which is equal to ``char_arr[5]``

That happen as the ``+`` arithemtic in pointer actually depends on the variables' declare pointer type.

``char_ptr2 = char_ptr1 + 1`` (as ``char`` pointer) will increase ``char_ptr2`` by ``1 * 1 byte`` register from ``char_ptr1`` where 1 byte is the size of ``char``.

``int_ptr2 = int_ptr1 + 1`` (as ``int`` pointer) will increase ``int_ptr2`` by ``1 * 4 byte`` register from ``int_ptr1`` where 4 byte is the size of ``int``.

Those can be clarify from those debug lines:

```c
printf("char_ptr1: %p, int_ptr1: %p\n", char_ptr1, int_ptr1);//char_ptr1: 0x7ffebc027653, int_ptr1: 0x7ffebc027653
printf("char_ptr2: %p, int_ptr2: %p\n", char_ptr2, int_ptr2);//char_ptr2: 0x7ffebc027654, int_ptr2: 0x7ffebc027657
```

## Related issue

1. [Set GPIO value in kernel space with ioread(), iowrite()](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/blink_led_with_iowrite32.c)

As all led_address led_on_address led_off_address are defined as unsigned int pointer, ``+`` arithmetic for them will be add with 4 bytes multiple in the register address, i.e ``7*4``, ``10*4`` for the register address increment for ``led_on_address`` and ``led_off_address`` correspondingly.

```c
unsigned int *led_address;
unsigned int *led_on_address;
unsigned int *led_off_address;

led_address = gpio_base + LED/10; //Set virtual address for LED pin
led_on_address = gpio_base + 7; //Set virtual address for ON address
led_off_address = gpio_base + 10; //Set virtual address for OFF address
```

[Set GPIO by macro in Raspberry C Direct Memory access in userspace example also has the same implementation](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Physical%20layer/GPIO/direct_register_access_control_gpio.c), as value define in macro are ``int`` type by default:

```c
#define GPIO_SET(addr,pin) *(addr+7)=1<<pin //Set GPIO in GPSET0
#define GPIO_CLR(addr,pin) *(addr+10)=1<<pin //Clear GPIO in GPCLR0
```

2. [Set GPIO value in Raspbian by busybox devmem](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Physical%20layer/Direct%20register%20access.md)
