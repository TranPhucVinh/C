## sprintf()

```c
int sprintf ( char * str, const char * format, ... );
```

Composes a string with the same text that would be printed if format was used on ``printf()``, but instead of being printed, the content is stored as a C string in the ``buffer`` pointed by ``str``. This function can be used to convert an int to a string.

### Example

```cpp
char buffer[50];
int n, a=5, b=3;
n = sprintf (buffer, "%d plus %d is %d", a, b, a+b);
printf ("[%s] is a string %d chars long\n",buffer,n);
```

```
[5 plus 3 is 8] is a string 13 chars long
```

Convert an int to a string (``uint32_t`` to ``char[]``)

```cpp
char clockValue[100];
uint32_t int32Number = 600000000;

sprintf(clockValue, "%d", int32Number); //convert uint_32 to string char[]
printf("%s\n", clockValue);
```

### Error

If the message length to form is bigger than the storage buffer, there will be an overflow, then the message could get copied to the memory address of message, with will effect other variable inside the program. This case especially happen to data structure like ``union ``.

E.g:

```c
char displayedString[5];
int a = 100, b = 100;
sprintf(displayedString, "%d%d", a, b);
```

Although overflow will not happen in this case but if ``displayedString`` is a member inside an ``union``, it will cause error to other variable inside the union.

## strcpy()

```c
char* strcpy(char* destination, const char* source);
```
``strcpy()`` returns the copied string.

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

## strncpy() 

Copy **n** character from **src** string to **dst** string.

```c
char *strncpy(char *dest, const char *src, size_t n)
```

```cpp
char helloWorld[] = "Hello world 10 times";
char dest[12];
strncpy(dest, helloWorld, 2);
printf("%s \n",dest); //He
```

## bcopy()

Copy ``n`` bytes from the area pointed to by ``s1`` to the area pointed to by ``s2``.

```c
void bcopy(const void *s1, void *s2, size_t n);
```
**Example**
```c
char s1[] = "Hello, World !";
char s2[100];

bcopy(s1, s2, 3);
puts(s2); //Hel
```
