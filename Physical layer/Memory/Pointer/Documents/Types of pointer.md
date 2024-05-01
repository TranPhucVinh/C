# Type casting pointer

Type casting pointer from smaller type ``char`` to bigger type ``int``:

```c
char char_val = 1;
char* char_ptr;

int* u_ptr;

char_ptr = &char_val;
u_ptr = (int*)&char_val;

printf("char_ptr: %p, u_ptr: %p\n", char_ptr, u_ptr);//char_ptr: 0x62FE0F, u_ptr: 0x62FE0F

printf("*char_ptr %d, *u_ptr %d\n", *char_ptr, *u_ptr);//*char_ptr 1, *u_ptr: 1660817153
```

Although both ``char_ptr`` and ``u_ptr`` has the same address, but as type is different, so ``*u_ptr`` has garbage value.

Type casting pointer from bigger type ``int`` to smaller type ``char``:

```c
int int_val = 0x1234;
int *int_ptr;
char* char_ptr;

int_ptr = &int_val;
char_ptr = (char*)&int_val;

printf("char_ptr: %p, int_ptr: %p\n", char_ptr, int_ptr);//char_ptr: 0x62FE0C, u_ptr: 0x62FE0C

printf("*char_ptr 0x%x, *int_ptr 0x%x\n", *char_ptr, *int_ptr);//*char_ptr 0x34, *int_ptr: 0x1234
```

# Wild pointer

A pointer that is not initialized to any valid address or NULL is considered as **wild pointer**. Wild pointer point to some arbitrary memory location and may cause a program to crash or behave badly.

```c
int main()
{
  int *p;  /* wild pointer */
   /* Some unknown memory location is being corrupted. 
   This should never be done. */ 
  *p = 12; 
}
```

This is a wrong declaration and operation that must be avoided:

```c
int *number = 12;//Wild pointer
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

**Note**: Except char pointer as string declarion (``char *displayed_string = "Hello, World !"``), you musn't set the value to the pointer variable when defining them:

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

# Pointer and const

## pointer to const

String declaration with pointer is highly recommended to use ``const char*``:

```c
const char *displayedString = "Hello, World !";
```

``const`` pointer for other variable

```c
/*
	int const* pointer or const int* pointer will give the same result
*/
const int *pointer;

int a = 10, b = 20;
pointer = &a;
printf("pointer: %d\n", *pointer);//10
a = 19;
printf("pointer: %d\n", *pointer);//19
pointer = &b;
printf("pointer: %d\n", *pointer);//20
```

## const pointer

A const pointer doesn't allow the pointer to change the address at later state of the program.

This gives compilation error in ``GCC`` and ``G++``:

```c
int a = 2, b = 10;
int* const pointer;
pointer = &a;//This give compilation error in GCC
```
Set value for ``int* const pointer``:
```c
int a = 2, b = 10;
int* const pointer = &a;
printf("%d\n", *pointer);//2

//Setting pointer to other address now give compilation error in GCC and G++
//pointer = &b;
```
## Const pointer to a const integer

```c
int const * a const;
```

# NULL pointer

Null pointer actually means a pointer that does not point to any valid location. We define a pointer to be null when we want to make sure that the pointer does not point to any valid location and not to use that pointer to change anything. If we don't use null pointer, then we can't verify whether this pointer points to any valid location or not.

```c
int a = 10;

int main () {
	int *ptr = NULL;
	ptr = &a;
	printf("%d",  *ptr);//10
}   
```

**Error**: If get ``*ptr`` after declaring NULL, there will segment fault error

```c
int a = 10;
int *ptr = NULL;
printf("%d",  *ptr);//Segment fault
ptr = &a;
printf("%d",  *ptr);
```
