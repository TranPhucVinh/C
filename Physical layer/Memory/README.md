# Fundemental concepts

## Memory type

Stack and heap memory are both stored on RAM of the PC.

### Stack memory

Stack memory is a temporary memory allocation scheme where the data members are accessible only if the method that contained them is currently is running. Stack memory block is allocated when the source code is compiled. Variables inside the stack memory block of a function are freed up after its execution.

Size of a stack memory block inside the program are fixed. If there is not enough stack memory as calling many nested functions or multiple times of recursion, stack overflow error might happen.

```c
int main()
{
   // All these variables get memory allocated on stack
   int a;
   int b[10];
   int n = 20;
   int c[n];
}
```

### Heap memory

**Dynamic Memory Allocation** can be defined as a procedure in which the size of a data structure (like array) is changed during the runtime. Variables inside heap memory block are not automatically freed up after execution but are required to be freed up by code (``free`` or ``delete``).

Heap memory block is allocated during run-time. When the size of heap memory is not enough for the program, the OS has the mechanism to increase the heap memory size.

## Data alignment 

### How does CPU access a variable ?

A 8-bit CPU can access a 1 byte (8-bit) variable in 1 CPU cyle. So for a n-byte variable, it takes the CPU ``n`` CPU cycle to access

A 64-bit CPU can access a 8 byte (64-bit) variable in 1 CPU cyle. So for a 8*n byte variable, it takes the CPU ``n`` CPU cycle to access

### Data alignment

In present day CPU, the read/write operation depend on the size of ``word`` (32-bit OS has ``word`` size of 4 byte). Data aligment is the way of arranging data so that its size is the multiple of ``word``, i.e ``4*k`` bytes (``k`` = 0, 1, 2,...). For **data alignment**, we have to add the **dummy byte** in some cases, sometimes known as **padding data**. Data alignment will increase the performance of the system as the read/write operation on the block data now have the size of multiples of word.

## Pointer

# API
