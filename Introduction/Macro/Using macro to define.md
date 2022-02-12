### Define variable with macro

Define an int variable with a macro function

```c
#define DEFINE_INT_VARIABLE(id) int id

int main()
{  
 DEFINE_INT_VARIABLE(a);
 a = 29;
 printf("%d\n", a);//29
}
```

### The difference between #if defined() and #ifdef()

The difference between the two is that ``#ifdef`` can only use a single condition, while ``#if defined(NAME)`` can do compound conditionals.

```c
#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#elif defined(UNIX) && !defined(WIN32)
/* Do linux stuff */
#else
/* Error, both can't be defined or undefined same time */
#endif
```

### Redefine macro value

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
### Predefine 

Predefine during compilation using flag ``-D``

```c
#include <stdio.h>

//Variable name is not define
main(){
	printf("name: %d \n", name);
}	
```

Predefine during compilation: ``gcc -D name=12 test.c``

Result: ``name: 12``

Predefine with ``#ifndef``

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