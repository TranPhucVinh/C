### Error with unary operation (pointer)

```c
#define a 6
printf("before %d \n", &a);
```

This will give error ``lvalue required as unary ‘&’ operand``. This happen because ``a`` is ``6`` which is not ``lvalue``.

### The difference between #if defined() and #ifdef()

The difference between the two is that #ifdef can only use a single condition, while ``#if defined(NAME)`` can do compound conditionals.

```c
#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#elif defined(UNIX) && !defined(WIN32)
/* Do linux stuff */
#else
/* Error, both can't be defined or undefined same time */
#endif
```