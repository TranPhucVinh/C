## strtok()

```cpp
char * strtok ( char * str, const char * delimiters );
```

A sequence of calls to this function split ``str`` into tokens, which are sequences of contiguous characters separated by ``any of the characters`` that are part of delimiters. **delimiters** only accept 1 character, if there is more than 1 character, there will segment fault error.

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

Passing more then 1 character for delimiters cause segment fault error

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

## strstr()

``strstr()``: Returns a pointer to the first occurrence of ``str2`` in ``str1``, or a null pointer if ``str2`` is not part of ``str1``.

**Return**: A pointer to the first occurrence in str1 of the entire sequence of characters specified in str2, or a null pointer if the sequence is not present in ``str1``.

Find a first part and second part of a string splitted by a substring with ``strstr()``

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char displayed_string[] = "Hello, World !";
char *second_part = NULL;
char *first_part;

int main(int argc, char *argv[]){
    second_part = strstr(displayed_string, "or");
	if (second_part != NULL)	printf("%s\n", second_part);//orld !
	else printf("NULL\n");

	first_part = (char*) malloc((second_part - displayed_string) * sizeof(char));
	
    //Copy (second_part - displayed_string) character from displayed_string to first_part
    strncpy(first_part, displayed_string, second_part - displayed_string);
    printf("%s\n", first_part);//Hello, W
	free(first_part);
}
```

Split a string by substring

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *remove_substring(char *string, char *sub) {
    char *new_string = (char*) malloc(strlen(string) * sizeof(char));
    char *second_part = (char*) malloc( (strlen(string) - strlen(sub)) * sizeof(char));

    char *match;
    int len = strlen(sub);

    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(second_part, match+len);
    }

    strcat(new_string, string);//string now has the value of the first part of char *string
    strcat(new_string, second_part);
    free(second_part);

    return new_string;
}
 
int main(int argc, const char *argv[]) {
    char test[] = "Hello, World!";
    char *new_string = remove_substring(test, "ll");
    printf("%s\n", new_string);
    free(new_string);
    return 0;
}
```

**Result**: ``Heo, World!``

### Replace substring inside a string

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char displayed_string[] = "String 1 underscore String 2";

char *replace_string_by_substring(char *original_string, char *substring, char *replace);

int main(){
    char *new_string = replace_string_by_substring(displayed_string, "underscore", "_");
    printf("%s\n", new_string);//String 1 _ String 2
    free(new_string);
}

char *replace_string_by_substring(char *orginal_string, char *substring, char *replace){
    char* match = strstr(orginal_string, substring);
    if(match)
    {
        int new_size = strlen(orginal_string) - strlen(substring) + strlen(replace) + 1;
        char* new_string = (char*) malloc(new_size);
        bzero(new_string, new_size);
        *match = '\0';
        strcat(new_string, orginal_string);
        strcat(new_string, replace);
        strcat(new_string, match + strlen(substring));
        return new_string;
    }
    else return NULL;
}
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

## itoa()

``itoa()`` converts an integer value to a null-terminated string using the specified ``base``.

```c
char *itoa ( int value, char * str, int base );
```

``itoa()`` is not defined in ANSI-C and is not part of C++, but is supported by some compilers. Use ``sprintf()`` instead.

## strrev()

``strrev()`` is used to reverse a string and works only with older versions of Microsoft C.

To reverse a string with raw string API: [Reverse string example](https://github.com/TranPhucVinh/C/blob/master/Introduction/Data%20structure/String/String%20parsing%20examples.md#example-4)
