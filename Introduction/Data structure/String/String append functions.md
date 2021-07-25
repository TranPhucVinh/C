## strncat()

```cpp
char *strncat(char *dest, const char *src, size_t n)
```

* ``dest``: the string where we want to append.
* ``src``: the string from which ‘n’ characters are going to append.
* ``n``: represents the maximum number of character to be appended. size_t is an unsigned integral type.

```c
char hw[] = "Hello, World!";
char addedChar[] = "abc";
strncat(hw, addedChar, 3); //Hello, World!abc   
```

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
    printf("Count: %d\n", count);
    count--;
  }
}
```

Result (infinite error loop)

```
Count: 1633771839
Count: 1633771838
Count: 1633771837
```

### Problem solved

To use ``strcat()`` in a loop, the displayedString must have the size which is bigger than the later expected concatenated string to store the value. If the size is smaller than the expected string, there will still be the infinite error loop.

Change the size of ``displayedString`` to be bigger: ``char displayedString[30] = "Received from PC: ";``

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