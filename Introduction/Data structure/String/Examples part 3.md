### Example 3

Split number and character from a string with ``strtol()``

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "12Hello";
    char *ptr;
    long ret;

    ret = strtol(str, &ptr, 10);
    printf("The number (unsigned long integer) is %ld\n", ret);
    printf("String part is: %s\n", ptr);
    if (!strlen(ptr)) puts("ptr null");
    return(0);
}
```
**Output**

```
The number (unsigned long integer) is 12
String part is:Hello
```

Parse a string include hex number

```c
#include <stdio.h>

int main(void)
{
    char sendString[] = "ab";
    int number = strtol(sendString, NULL, 16);
    printf("%d\n", number);//171
    return(0);
}
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