## strcat()

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

### strcat() in a loop

```c
char addedString[] = "a";
char displayedString[] = "Received from PC: ";
int count = 10;

int main(){
  while (count) {
    strcat(displayedString, addedString);
    printf("displayedString %s, count %d\n", displayedString, count);
    count--;
  }
}
```

Result (infinite error loop)

```
displayedString Received from PC: aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa, count 1633771797
displayedString Received from PC: aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa, count 1633771796
displayedString Received from PC: aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa, count 1633771795
```

### Problem solved

To use ``strcat()`` in a loop, the ``displayedString`` must have the size which is bigger than the later expected concatenated string to store the value. If the size is smaller than the expected string, there will still be the infinite error loop.

Change the size of ``displayedString`` to be bigger: ``char displayedString[30] = "Received from PC: ";``

## strncat()

```cpp
char *strncat(char *dest, const char *src, size_t n)
```

* ``dest``: the string where we want to append.
* ``src``: the string from which ‘n’ characters are going to append.
* ``n``: represents the maximum number of character to be appended. size_t is an unsigned integral type.

```c
char displayedString[] = "Hello, World!";
char addedChar[] = "abc";
strncat(displayedString, addedChar, 3); //Hello, World!abc   
```

However, using ``char displayedString[]`` for strncat will result in error concatentation. Take this example: 

```c
int count = 10;
char displayedString[] = "Hello, World!";
char addedChar[] = "abc";

while (count) {
  strncat(displayedString, addedChar, 3);
  printf("displayedString: %s, count: %d\n", displayedString, count);
  strcpy(displayedString, "Hello, World!");
  count--;
}
```
```c
displayedString: Hello, World!abc, count: 10
displayedString: Hello, World!bc, count: 9
displayedString: Hello, World!c, count: 8
displayedString: Hello, World!, count: 7
displayedString: Hello, World!, count: 6
...
```
**Problem solved**: ``char displayedString[20] = "Hello, World!";``

## Dynamically append a char pointer as string

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_append(char **str, const char *str2) {
    char *tmp = NULL;

    // Reset *str
    if ( *str != NULL && str2 == NULL ) {
        free(*str);
        *str = NULL;
        return;
    }

    // Initial copy
    if (*str == NULL) {
        *str = (char*) malloc( strlen(str2)+1);
        memcpy(*str, str2, strlen(str2));
    }
    else { // Append
        tmp = (char*) malloc(strlen(*str)+1);
        memcpy(tmp, *str, strlen(*str));
        *str = (char*) malloc(strlen(*str)+strlen(str2)+1);
        memcpy( *str, tmp, strlen(tmp) );
        memcpy( *str + strlen(*str), str2, strlen(str2) );
        free(tmp);
    }

}

int main(int argc, char *argv[]) {
    char *str = "one";
    string_append(&str, ",");
    string_append(&str, "two");
    string_append(&str, ",three");

    printf("str=%s\n", str);

    string_append(&str, NULL);
    return 0;
}
```

## strol()

```c
long int strtol(const char *str, char **endptr, int base)
```

Split number and character from a string with ``strtol()``: ``Split number and character from a string with strtol()`` in ``Examples part 3.md``

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