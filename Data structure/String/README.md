# Operations

* [Char array as string](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/Char%20array%20as%20string.md)
* [Char pointer as string](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/Char%20pointer%20as%20string.md)

# API

## [String copy functions](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/String%20copy%20functions.md)

* [sprintf()](String%20copy%20functions.md#sprintf)
* [snprintf()](String%20copy%20functions.md#snprintf)
* [strcpy()](String%20copy%20functions.md#strcpy)
* [strncpy()](String%20copy%20functions.md#strncpy)
* [strdup()](String%20copy%20functions.md#strdup)
* [bcopy()](String%20copy%20functions.md#bcopy)

## [String append functions](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/String%20append%20functions.md)

* [strtok()]()
* strol()
* strtoul()
* strstr()
* [atoi()](#atoi)
* itoa()
* strrev()

### atoi()

Include in library **stdlib.h**.

```c
int atoi(const char *str)
```
Converts the string argument **str** to an integer (type int).  If no valid conversion could be performed, it **returns zero**.

**E.g**

```c
char str[] = "C programming with GNU-GCC";
int a = atoi(str);
printf("%d \n", a); //0
```   

```c
char str[] = "1234";
int a = atoi(str);
printf("%d \n", a); //1234
```

The function stops reading the input string at the first character that it cannot recognize as part of a number.

```c
char str[] = "123abc";
int a = atoi(str);
printf("%d \n", a); //123
```

### itoa()

``itoa()`` converts an integer value to a null-terminated string using the specified ``base``.

```c
char *itoa ( int value, char * str, int base );
```

``itoa()`` is not defined in ANSI-C and is not part of C++, but is supported by some compilers. Use ``sprintf()`` instead.

### strrev()

``strrev()`` is used to reverse a string and works only with older versions of Microsoft C.

To reverse a string with raw string API: [Reverse string example](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/String%20parsing%20examples.md#example-4)


## String parsing functions

* [strtok()](#strtok)
* [strtol()](#strtol)
* [strtoul()](#strtoul)
* [strstr()](#strstr)

### strtok()

```cpp
char *strtok( char * str, const char * delimiters );
```

A sequence of calls to this function split ``str`` into tokens, which are sequences of contiguous characters separated by ``any of the characters`` that are part of delimiters. **delimiters** only accept 1 character, if there is more than 1 character, there will segment fault error.

**On a first call**, the function expects a C string as argument for ``str``, whose first character is used as the starting location to scan for tokens.

**In subsequent calls**, the function expects a null pointer and uses the position right after the end of the last token as the new starting location for scanning.

### strtol()

```c
#include <stdlib.h>
long int strtol(const char *str, char **endptr, int base)
```

### strtoul()

Convert a string to unsigned long

```c
unsigned long int strtoul (const char *__restrict __nptr, char **__restrict __endptr, int __base)
```
**Example**
```c
strtoul("12asdas", NULL, 10);   //12
strtoul("Hello", NULL, 10);     //0
```
Problem with ``char`` number
```c
char number = strtoul("127", NULL, 10);   //127
char number = strtoul("128", NULL, 10);   //-128
```

**Explain**: This happens as ``char`` is defined as ``signed char`` by default. 

### strstr()

```c
char *strstr (const char *s1, const char *s2);
```

Returns a pointer to the first occurrence of ``str2`` in ``str1``, or a null pointer if ``str2`` is not part of ``str1``.

# Examples

## [String remove examples](String%20remove%20examples.md)

* [Remove garbage value of a string](String%20remove%20examples.md#remove-garbage-value-of-a-string)