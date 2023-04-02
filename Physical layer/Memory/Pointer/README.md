In computer science, a **reference** is a value that enables a program to indirectly access a particular ``datum``, such as a variable's value or a record, in the computer's memory or in some other storage device. **Pointers** are the most primitive type of reference.

The parameter to a function can be a copy of a value that is represented by variable, which is known as **pass by value**, or can be a reference to a memory space that stores value of variable, which is known as **pass by reference**.

A pointer is a variable that stores address of other variable. All the pointer syntax works identically in both C/C++.

* ``*p``: declare a pointer
* ``*p``: value at address
* ``&``: get the address of the variable
* ``%p``: is used to print out the address as it can print out the hex value.

# [Fundamental concepts](Fundamental%20concepts.md)

Fundamental concepts of pointer includes:

* [Declare pointer](Fundamental%20concepts.md#declare-pointer):
* [Size of the pointer variable](Fundamental%20concepts.md#)
* [Get value of pointer](Fundamental%20concepts.md#)
* [Set value for pointer](Fundamental%20concepts.md#): [Must not directly set value for a pointer deferencing (i.e *pointer)]() and [must not arbitrarily set value at specific register address]()
* [Pointer and array](Pointer%20and%20Array.md)
* [Pointer to pointer]() or double pointer
* [Function pointer](Function%20pointer.md)

Comparing the different between pointer and reference is only available in [CPP](https://github.com/TranPhucVinh/Cplusplus) as CPP support [lvalue](https://github.com/TranPhucVinh/Cplusplus/blob/master/Physical%20layer/Memory/lvalue.md) and [rvalue reference](https://github.com/TranPhucVinh/Cplusplus/blob/master/Physical%20layer/Memory/rvalue.md).

# Implementation

* Pass by reference vs Pass by value: [Change value of variable by pointer in a function](Implementations.md#change-value-of-variable-by-pointer-in-a-function)

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

## Related issues

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
