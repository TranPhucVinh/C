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

## Pointer


# API
