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
* atoi()
* itoa()
* strrev()

## atoi()

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

## itoa()

``itoa()`` converts an integer value to a null-terminated string using the specified ``base``.

```c
char *itoa ( int value, char * str, int base );
```

``itoa()`` is not defined in ANSI-C and is not part of C++, but is supported by some compilers. Use ``sprintf()`` instead.

## strrev()

``strrev()`` is used to reverse a string and works only with older versions of Microsoft C.

To reverse a string with raw string API: [Reverse string example](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/String%20parsing%20examples.md#example-4)

## [String remove examples](String%20remove%20examples.md)

* [Remove garbage value of a string](String%20remove%20examples.md#remove-garbage-value-of-a-string)
