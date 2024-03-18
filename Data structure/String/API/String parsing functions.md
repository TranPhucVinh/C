# strtok()
```c
char *strtok(char *str, const char * delimiters );
```

A sequence of calls to this function split ``str`` into tokens, which are sequences of contiguous characters separated by ``any of the characters`` that are part of delimiters. **delimiters** only accept 1 character, if there is more than 1 character, there will segment fault error.

**On a first call**, the function expects a C string as argument for ``str``, whose first character is used as the starting location to scan for tokens.

**In subsequent calls**, the function expects a null pointer and uses the position right after the end of the last token as the new starting location for scanning.

## Split string ABCD seperated by character C

```cpp
har orgin_string[] = "ABCD";
char *separator;
separator = strtok(orgin_string, "C");
printf("%s %s\n", separator, orgin_string); //AB AB; separator and orgin_string now are equal to each other
```

Passing more than 1 character for delimiters cause segment fault error

```c
//This is wrong and cause Segment fault error
char* splitString = "ABCD";
separator = strtok(splitString, "BC");
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

## Split string for csv data

```c
char csv_data[] = "data_1,data_2,_data_3";

char *data_1, *data_2, *data_3;

data_1 = strtok(csv_data,",");
data_2 = strtok (NULL, ",");
data_3 = strtok (NULL, ",");
printf("data 1 %s, data 2: %s, data 3: %s\n", data_1, data_2, data_3);
```

# strtol()
Split number and character from a string

```c
#include <stdlib.h>
long int strtol(const char *str, char **endptr, int base)
```
## Split number and character from a string 

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
# strtoul()

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
# strstr()

```c
char *strstr (const char *s1, const char *s2);
```

Returns a pointer to the first occurrence of ``str2`` in ``str1``, or a null pointer if ``str2`` is not part of ``str1``. Check [strstr() example](strstr()%20examples.md) for its implementation.
# tolower()

```c
#include <stdio.h>
#include <ctype.h>
int main()
{
    char c, result;

    c = 'M';
    result = tolower(c);
    printf("tolower(%c) = %c\n", c, result);

    c = 'm';
    result = tolower(c);
    printf("tolower(%c) = %c\n", c, result);

    c = '+';
    result = tolower(c);
    printf("tolower(%c) = %c\n", c, result);
    
    return 0;
}
```
