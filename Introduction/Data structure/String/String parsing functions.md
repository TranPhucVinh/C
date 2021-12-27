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
Serial.println(separator); //AB
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
**Example 2**: Split string ``Hello,{World!}`` by ``{``.

```c
char rawString[] = "Hello,{World!}";
char *splitString;

splitString = strtok(rawString,"{");
printf("%s\n", splitString);//Hello,
splitString = strtok (NULL, "");
printf("%s\n", splitString);//World!}
```

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
