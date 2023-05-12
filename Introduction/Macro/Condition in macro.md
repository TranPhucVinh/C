# #if defined

```c
#include <stdio.h>
#define CHANGE_VALUE

#if defined(CHANGE_VALUE)
int value = 1;
#else
int value = 2;
#endif

int main(){
    printf("value %d\n", value);
}
```
**Result**: ``value 1``:

**Note** ``#define`` must be used before ``#if defined``. If using after ``#if defined``, it won't take effect:
```c
#if defined(CHANGE_VALUE)
int value = 1;
#else
int value = 2;
#endif

int main(){
    #define CHANGE_VALUE
    printf("value %d\n", value);//2, while expect it to be 1
}
```

Without ``#define CHANGE_VALUE``:

```c
#include <stdio.h>
// #define CHANGE_VALUE

#if defined(CHANGE_VALUE)
int value = 1;
#else
int value = 2;
#endif

int main(){
    printf("value %d\n", value);
}
```
**Result**: ``value 2``

Same result with ``#ifdef``. Note that ``#ifdef`` doesn't go with ``()`` and ``:``:

```c
#define CHANGE_VALUE

#ifdef CHANGE_VALUE
    int value = 1;
#else
    int value = 2;
#endif
```

Use ``#if defined`` to define multiple functions:

```c
#include <stdio.h>

#define DEFINE_FUNCTION
#if defined(DEFINE_FUNCTION)
void add_function(int a, int b)
#else
void add_function(int a, int b, int c)
#endif
{
    int general_var = 123;//Put general defines here, before #if and #else
    #if defined(DEFINE_FUNCTION)
    printf("#if defined(DEFINE_FUNCTION): %d", a+b+general_var);
    #else
    printf("#if defined(DEFINE_FUNCTION): %d", a+b+c+general_var);
    #endif
}
int main(){
    add_function(1, 2);
}
```

Application:

* Linked list: Insert a node at first index by using double pointer, as well as inserting at other index: [multiple_defines_for_insert_with_index.c](../../Data%20structure/Linked%20list/Singly%20linked%20list/multiple_defines_for_insert_with_index.c)

# The difference between #if defined() and #ifdef()

The difference between the two is that #ifdef can only use a single condition, while #if defined(NAME) can do compound conditionals.

```c
#include <stdio.h>
#define CHANGE_VAR_A
#define CHANGE_VAR_B

#if defined (CHANGE_VAR_A) && defined(CHANGE_VAR_B)
    int value = 1;
#else
    int value = 2;
#endif

int main(){
    printf("value %d\n", value);//1
}
```
# Redefine macro value with undef

With ``#define``

```c
#define integerValue 190

printf("%d \n", integerValue);//190
#undef integeValue
#define integerValue 100
printf("%d \n", integerValue);//100
```

With traditional variable definition

```c
int integerValue = 200;
printf("%d \n", integerValue); //200
#undef integeValue
#define integerValue 100
printf("%d \n", integerValue); //100
```

With just ``#undef integeValue``, the value still unchanges
```c
printf("%d \n", integerValue); //190
#undef integeValue
printf("%d \n", integerValue); //190
```
# Predefine 

## Predefine during compilation using flag -D

```c
#include <stdio.h>

//Variable name is not define
main(){
	printf("name: %d \n", name);
}	
```

Predefine during compilation: ``gcc -D name=12 test.c``

Result: ``name: 12``

## Predefine with #ifndef

```c
#include <stdio.h>

#ifndef name
#define name 4
#endif

main(){
	printf("name: %d \n", name);
}	
```

If compile ``gcc -D name=12 test.c``, then result is ``name: 12``
