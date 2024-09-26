# Fundamental concepts

**Inline function** are those function whose definitions are small and can be substituted at the place where its function call is happened. Function substitution is totally compiler choice. The argument passing and stack maintenance is skipped and it results in faster code execution, but it increases code size, particularly if the inline function is large or one inline function is used often

```c
#include <stdio.h>

inline int inline_function()
{
   return 2;
}
  
int main()
{
   int number;

   number = inline_function();

   printf("number: %d\n", number);
   return 0;
}
```

Compile in GCC gives error:

```
/tmp/ccRXFxiR.o: In function `main':
test.c:(.text+0xe): undefined reference to `inline_function'
collect2: error: ld returned 1 exit status
```

This error is one of the side effect of GCC the way it handle inline function. When compiled, GCC performs inline substitution as the part of optimisation. Normally GCC’s file scope is “not extern linkage”. That means inline function is never ever provided to the linker which is causing linker error, mentioned above.

**Problem solved**: Use “static” before inline. Using static keyword forces the compiler to consider this inline function in the linker.

```c
static inline int inline_function()
{
   return 2;
}
```
## Inline function to find min and max
```c
#include <stdio.h>

static inline int MAX(int a, int b) {
    return ((a) > (b) ? (a) : (b));
} 

static inline int MIN(int a, int b) {
   return ((a) < (b) ? (a) : (b));
}

int main() {
    int x = 10, y = 20;

    printf("Max of %d and %d is %d\n", x, y, MAX(x, y));
    printf("Min of %d and %d is %d\n", x, y, MIN(x, y));
}
```
# Compare macro function and inline function

With macro function, we can write type insensitive functions but it is also the disadvantage of macro function as macro functions can't do validation check.

Inline function cares the type of function argument and return type.

Both macro and inline function increase the size of the executable.
