# Build stack with array

Program: [stack_with_array.c](stack_with_array.c)

This example is intended for comprehensive and easy to understand the stack created operation.

# Build stack with array, using [struct](../struct/)

Program:[stack_with_array_and_struct.c](stack_with_array_and_struct.c). This example is intended for OOP.

As function as struct member must be defined by function pointer, [implementing a stack in C by struct](stack_with_array_and_struct.c) will never be efficient when comparing to CPP OOP technique.

As implementing a stack with C struct function member requires the globally defined function which are later passed into that struct function member, the  [stack_with_array_and_struct.c](stack_with_array_and_struct.c) program has inefficient issues which can't be solved when not using OOP:

* ``int stack_arr[STACK_SIZE]`` and ``int top`` must be global variables in order to be shared between globally defined push() and pop(), although ``push()`` and ``pop()`` are also ``struct _Stack`` functions. It would be better if ``int stack_arr[STACK_SIZE]`` and ``int top`` are kept privately inside ``struct _Stack``.
* ``is_empty()`` and ``is_full()`` work independantly from ``stack`` object (``Stack stack``), as they're hard-mapped to ``int stack_arr[STACK_SIZE]``, while it's better to make those functions depend on every ``stack`` object.

All those inefficient issues can be solved completely when using CPP OOP, check [stack_with_array_and_struct.cpp](https://github.com/TranPhucVinh/Cplusplus/blob/master/Data%20structure/Stack/stack_with_array.cpp)