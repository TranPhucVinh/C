# strtok(): Split string

Split string ``ABCD`` seperated by character ``C``

```cpp
char* splitString = "ABCD";
char* separator;
separator = strtok(splitString, "C");
printf("%s", separator); //AB
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

# strtok(): Split string for csv data

```c
char csv_data[] = "data_1,data_2,_data_3";

char *data_1, *data_2, *data_3;

data_1 = strtok(csv_data,",");
data_2 = strtok (NULL, ",");
data_3 = strtok (NULL, ",");
printf("data 1 %s, data 2: %s, data 3: %s\n", data_1, data_2, data_3);
```

# strtol(): Split number and character from a string 

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
