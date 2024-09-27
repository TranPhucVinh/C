**Pointer to pointer** is also called **double pointer**.

# Define a double pointer and use it to change the variable's value

```c
#include <stdio.h>

int number = 9;

int *pointer = &number;
int **double_pointer = &pointer;

int main(){
	printf("*pointer: %d \n", *pointer);//9
	printf("Address of pointer: %p \n", &pointer);//0x601040
	printf("double_pointer: %p \n", double_pointer);//0x601040
	printf("**double_pointer: %d \n", **double_pointer);//9
	
    //Now use double pointer to change variable value
    **double_pointer = 10;
    printf("**double_pointer: %d \n", **double_pointer);//10
    printf("number: %d \n", number);//10
}
```

# Define double pointer on heap memory for 2 dimension array

All define for 2 dimension array with double pointer must have type like:

```c
#define ROW_SIZE 4
int **int_array = (int**) malloc(ROW_SIZE * sizeof(int*));
```

Take this picture for an example with the register address

![](../../../../Environment/Images/double_pointer_with_register_size.png)

As double pointer stores the address of other pointers, so size of pointer (e.g ``sizeof(int*)``, ``sizeof(char*)``,...), which is a constant, is needed to get the register's size.

As ``sizeof(int*)`` returns the size of the register (e.g any register in the picture like ``0x7E200000``, ``0x7E200004``,...), so ``ROW_SIZE * sizeof(int*)`` will tell how many register is needed. ``int_array`` now stores the information that how many registers is needed to stored the registers/address of other pointers.

If apply the double pointer allocating to the picture above, 4 registers ``0x7E200000``, ``0x7E200004``, ``0x7E200008``, ``0x7E20000C`` will be used to stored the address of other variables.

In that system, for example register ``0x7E20001C`` has variable value ``123``, same for ``0x7E200020`` with 456, ``0x7E200024`` with ``789`` and ``0x7E200028`` with ``246``.

Then ``int_array`` will store those register address like in the picture above.

That's why ``int_array`` must be allocated to have enough size to store the address value. E.g  ``0x7E200000`` store  ``0x7E20001C``.

For other data type like char, the define must be:

```c
#define ROW_SIZE 4
char **char_array = (char**) malloc(ROW_SIZE * sizeof(char*));
```

**Application**: [Two dimension array on heap memory](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/Array/Two%20dimension%20array%20on%20heap%20memory.md)

# Define double pointer for a variable

* Double pointer as a variable is used as the returned value from a POSIX thread, check [Thread creation: Get return from a thread and store to a variable](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Thread/Examples.md#get-return-from-a-thread-and-store-to-a-variable) for its implementation.
* Function ``insert_node_at_index()`` for both [userspace](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/multiple_defines_for_insert_with_index.c) and [kernel space linked list](https://github.com/TranPhucVinh/C/blob/master/Kernel/Linked%20list/insert_with_index.c) use double pointer variable ``first_node`` to insert a new first node to replace it.
# Double pointer as function argument
At first, take a look at this example where a pointer wants to point to another variable address in order to change the orginal variable's value to the a new one:
```c
#include <stdio.h>

int a = 8;
int b = 10;

void foo(int *ptr)
{
	ptr = &a;
}

int main()
{
	int* ptr;
	ptr = &b;
	printf("*ptr: %d", *ptr);//10
	foo(ptr);
	printf("*ptr: %d", *ptr);//10, expected 8
	return 0;
}
```
We expect ``ptr`` to store the address value of ``a`` but ``ptr`` passed to ``foo()`` is the value of ``ptr`` (i.e ``&b``).

That happens because the pointer ptr in ``foo()`` is a local copy of the pointer you passed in main. When you do ``ptr = &a``, you change this local copy to point to a, but the original pointer in main (ptr in main) remains unchanged.

**That's why we need to use double pointer**:
```c
void foo(int **ptr) {
    *ptr = &a;  // Dereference the pointer to pointer and change the original pointer
}

int main() {
    int* ptr;
    ptr = &b;
    printf("*ptr: %d\n", *ptr); // 10
    foo(&ptr);                  // Pass the address of ptr
    printf("*ptr: %d\n", *ptr); // 8, now ptr points to 'a'
    return 0;
}
```
Beside double pointer, we can use ``memcpy()``:

```c
void foo(int *ptr)
{
	memcpy(ptr, &a, sizeof(int));
}

int main()
{
	int* ptr;
	ptr = &b;
	printf("*ptr: %d", *ptr);//10
	foo(ptr);
	printf("*ptr: %d", *ptr);//8
	return 0;
}
```
Or setting the pointer directly:
```c
void foo(int *ptr) {
	*ptr = a;
}
// main() kept same as memcpy()
```
