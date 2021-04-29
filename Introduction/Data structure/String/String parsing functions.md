### strtok()

```cpp
char * strtok ( char * str, const char * delimiters );
```

A sequence of calls to this function split ``str`` into tokens, which are sequences of contiguous characters separated by ``any of the characters`` that are part of delimiters.

**On a first call**, the function expects a C string as argument for ``str``, whose first character is used as the starting location to scan for tokens.

**In subsequent calls**, the function expects a null pointer and uses the position right after the end of the last token as the new starting location for scanning.

**Example**

Split string ``This is Hello, World string`` by space

```cpp
#include <stdio.h>
#include <string.h>

int main(){
    char rawString[] = "This is Hello, World string";
    char *splitString;
    
    splitString = strtok(rawString," ");

    while (splitString != NULL)
    {
        printf("%s\n", splitString);
        splitString = strtok (NULL, " ");
    }

    return 0;
}
```
**Result**

```
This
is
Hello,
World
string
```

## Append string

### strncat()

```cpp
char *strncat(char *dest, const char *src, size_t n)
```

* ``dest``: the string where we want to append.
* ``src``: the string from which ‘n’ characters are going to append.
* ``n``: represents the maximum number of character to be appended. size_t is an unsigned integral type.

```cpp
char hw[] = "Hello, World!";
char addedChar[] = "abc";
strncat(hw, addedChar, 3); //Hello, World!abc   
```

### strcat()

```c
char *strcat(char *dest, const char *src);
```
**Example**
```c
char hw[] = "Hello, World!";
strcat(hw, " abc");//Hello, World! abc
```
```c
char hw[] = "Hello, World!";
char addedChar[] = "abc";
strcat(hw, addedChar);//Hello, World! abc
```

To append a string with a char, add ``&``

```c
char hw[] = "Hello, World!";
char returnChar = 'a';
strncat(hw, &returnChar, 1); //Hello, World!a
```

## strol()

```c
long int strtol(const char *str, char **endptr, int base)
```

Split number and character from a string with ``strtol()``: ``Split number and character from a string with strtol()`` in ``Examples.md``

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

**Explain**: This happens as char is defined as signed char by default. 

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

### itoa()

``itoa()`` is used to convert from int to string but it is not an official function from C, use ``sprintf()`` instead.

Check ``sprintf()`` in ``String copy functions.md``.
