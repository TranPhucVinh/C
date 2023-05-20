# sprintf()

```c
int sprintf ( char * str, const char * format, ... );
```

Composes a string with the same text that would be printed if format was used on ``printf()``, but instead of being printed, the content is stored as a C string in the ``buffer`` pointed by ``str``. This function can be used to convert an int to a string. The real size of the format string is returned, not size of the string buffer used to store.

## Example

```cpp
int string_size;
char string_buffer[30];

string_size = sprintf(string_buffer, "%d", 12);
printf("%s %d\n", string_buffer, string_size);
string_size = sprintf(string_buffer, "%s", "Hello, World !");
printf("%s %d\n", string_buffer, string_size);
```

```
12 2
Hello, World ! 14
```

Convert an int to a string (``uint32_t`` to ``char[]``)

```cpp
char clockValue[100];
uint32_t int32Number = 600000000;

sprintf(clockValue, "%d", int32Number); //convert uint_32 to string char[]
printf("%s\n", clockValue);
```

# snprintf()

```c
char displayed_string[] = "String: %s ";
char buffer[50];

snprintf(buffer, 50, displayed_string, "Hello, World !");
printf("%s", buffer);//String: Hello, World ! 
```

## Error

If the message length to form is bigger than the storage buffer, there will be an overflow, then the message could get copied to the memory address of message, with will effect other variable inside the program. This case especially happen to data structure like ``union ``.

E.g:

```c
char displayedString[5];
int a = 100, b = 100;
sprintf(displayedString, "%d%d", a, b);
```

Although overflow will not happen in this case but if ``displayedString`` is a member inside an ``union``, it will cause error to other variable inside the union.

# strcpy()

```c
char* strcpy(char* destination, const char* source);
```
``strcpy()`` returns the copied string. Memory of ``destination`` must be allocated first (by char pointer or char array).

```cpp
char string[20];
strcpy(string,"Hello, World!!");
printf("string: %s\n", string); //string: Hello, World!!
```
**Note**: ``char* destination`` must have the size at least equal to the size of ``const char* source``. If ``char* destination`` has smaller size, there might be problem in the next operation of the program

**Example**

```c
char string1[3], string2[3];
strcpy(string1, "Hello, World !");
strcpy(string2, "Hello, World !");
printf("%s\n", string1);//HelHello, World !
printf("%s\n", string2);//Hello, World !
```

# strncpy() 

Copy ``n`` character from ``src`` string to ``dest`` string.

```c
char *strncpy(char *dest, const char *src, size_t n)
```

```cpp
char helloWorld[] = "Hello world 10 times";
char dest[12];
strncpy(dest, helloWorld, 2);
printf("%s \n",dest); //He
```

# strdup()

```c
strdup(const char* s);
```

``strdup()`` will return a new dynamically allocated char pointer duplicated from ``const char *s`` or return ``NULL`` if fail allocation. The new dynamically allocated char pointer resulted from ``strdup()`` should be then ``free()``.

```c
char *new_string = strdup("Hello, World !");
printf("%s", new_string);
free(new_string);
```

# bcopy()

Copy ``n`` bytes from the area pointed to by ``s1`` to the area pointed to by ``s2``.

```c
#include <strings.h>
void bcopy(const void *s1, void *s2, size_t n);
```
**Example**
```c
char s1[] = "Hello, World !";
char s2[100];

bcopy(s1, s2, 3);
puts(s2); //Hel
```
