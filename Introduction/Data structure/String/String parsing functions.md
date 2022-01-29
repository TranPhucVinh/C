## strtok()

```cpp
char * strtok ( char * str, const char * delimiters );
```

A sequence of calls to this function split ``str`` into tokens, which are sequences of contiguous characters separated by ``any of the characters`` that are part of delimiters.

**On a first call**, the function expects a C string as argument for ``str``, whose first character is used as the starting location to scan for tokens.

**In subsequent calls**, the function expects a null pointer and uses the position right after the end of the last token as the new starting location for scanning.

**Example 1**: Split string with ``strok()``

Split string ``ABCD`` seperated by character ``C``

```cpp
char* splitString = "ABCD";
char* separator;
separator = strtok(splitString, "C");
printf("%s", separator); //AB
```

Split string ``This is Hello, World string`` by space

```cpp
char rawString[] = "This is Hello, World string";
char *splitString;

splitString = strtok(rawString," ");

while (splitString != NULL)
{
    printf("%s\n", splitString);
    splitString = strtok (NULL, " ");
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
**Example 2**: Split string for csv data

```c
char csv_data[] = "data_1,data_2,_data_3";

char *data_1, *data_2, *data_3;

data_1 = strtok(csv_data,",");
data_2 = strtok (NULL, ",");
data_3 = strtok (NULL, ",");
printf("data 1 %s, data 2: %s, data 3: %s\n", data_1, data_2, data_3);
```

## strol()

```c
#include <stdlib.h>
long int strtol(const char *str, char **endptr, int base)
```

Split number and character from a string with ``strtol()``:

```c
char str[] = "12Hello";
char *ptr;
long ret;

ret = strtol(str, &ptr, 10);
printf("The number (unsigned long integer) is %ld\n", ret);
printf("String part is: %s\n", ptr);
if (!strlen(ptr)) puts("ptr null");
```

**Output**

```
The number (unsigned long integer) is 12
String part is:Hello
```

Parse a string include hex number

```c
char sendString[] = "ab";
int number = strtol(sendString, NULL, 16);
printf("%d\n", number);//171
```

Split the entered string from executed argument

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *ptr;
    long ret;

    if (argc > 1){
        ret = strtol(argv[1], &ptr, 10);
        printf("The number (unsigned long integer) is %ld\n", ret);
        printf("String part is:%s\n", ptr);
        if (!strlen(ptr)) puts("No string found in argument");
    } else puts("You haven't entered anything");   
    return(0);
}
```
**Input** ``./a.out 123abc``

**Output**

```
The number (unsigned long integer) is 123
String part is: abc
ptr null
```

**Input** ``./a.out 123``

**Output**

```
The number (unsigned long integer) is 123
String part is:
ptr null
```

## strtoul()

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

``itoa()`` converts an integer value to a null-terminated string using the specified ``base``.

```c
char *itoa ( int value, char * str, int base );
```

``itoa()`` is not defined in ANSI-C and is not part of C++, but is supported by some compilers. Use ``sprintf()`` instead.

### strrev()

``strrev()`` is used to reverse a string and works only with older versions of Microsoft C.

To reverse a string with raw string API: [Reverse string example](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/String%20parsing%20examples.md#example-4)