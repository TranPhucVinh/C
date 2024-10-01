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
# Remove members from the array which has a member with a greater value anywhere to the right side of it

Case 1: array = [5,2,13,3,8], output: [13,8]

Explanation: The nodes that should be removed are 5, 2 and 3.
* Node 13 is to the right of node 5.
* Node 13 is to the right of node 2.
* Node 8 is to the right of node 3.

Case 2: array = [1,1,1,1], Output: [1,1,1,1]. Explanation: Every node has value 1, so no nodes are removed.

The general idea is to push and pop out the member of the stack based on condition.

Case 1: [5,2,13,3,8]

* Step 1: Stack is empty, so ``push(5)``. stack = [5]
* Step 2: ``get_top() = 5``. As 2 < get_top(), push(2). stack = [5, 2]
* Step 3: ``get_top() = 2``. As 13 > get_top(), so pop(). stack = [5]
* Step 4: Still with 13. ``get_top() = 5``. As 13 > get_top(), so pop(). stack = []. The stack now is empty so ``push(13)``. stack = [13]

Step 4 means that we will pop out the member of the stack which is smaller than the current value.
* Step 5: ``get_top() = 13``. As 3 < get_top() and we only pop out the member smaller than the current value (3 in this case), so we will push 3 into the stack (``push(3)``). stack = [13, 3]
* Step 6: Same with step 4, as get_top() = 3, we will pop out 3 from the stack (``pop()``) then push 8 in (``push(8)``).

Program: [rm_member_which_has_member_greater_than_it_from_the_right.c](rm_member_which_has_member_greater_than_it_from_the_right.c)
