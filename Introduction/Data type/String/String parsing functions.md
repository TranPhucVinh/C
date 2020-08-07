### ``strtok()``

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

### strncat() to append string

```cpp
char *strncat(char *dest, const char *src, size_t n)
```

* ``dest``: the string where we want to append.
* ``src``: the string from which ‘n’ characters are going to append.
* ``n``: represents the maximum number of character to be appended. size_t is an unsigned integral type.

```cpp
char hw[] = "Hello, World!";
strncat(hw, "abc", 3); 
printf("%s \n", hw); //Hello, World!abc   
```

**Example**: Append from index 0

```cpp
char firstChar[] = "First ";
const char hw[50] = "Hello, World!";
strncat(firstChar, hw, strlen(hw)); 
printf("%s \n", firstChar); //First Hello, World!
```

### strcat() to append string

```c
char *strcat(char *dest, const char *src);
```
**Example**
```c
char hw[] = "Hello, World!";
strcat(hw, " abc"); 
puts(hw); //Hello, World! abc
```