### Get a character in a string

```c
int main() {
    int i;
    char hello[] = "a character";
    printf("%c \n", hello[3]);
    return 0;
}
```

```
h 
```

### sprintf()

```c
int sprintf ( char * str, const char * format, ... );
```

Composes a string with the same text that would be printed if format was used on printf, but instead of being printed, the content is stored as a C string in the **buffer** pointed by **str**.

```c
#include <stdio.h>

int main (){
  char buffer[50];
  int n, a=5, b=3;
  n = sprintf (buffer, "%d plus %d is %d", a, b, a+b);
  printf ("[%s] is a string %d chars long\n",buffer,n);
  return 0;
}
```

```
[5 plus 3 is 8] is a string 13 chars long
```

**E.g**: Convert **uint32_t** to **string-char[]**

```c
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <stdint.h>

int main() {

  char clockValue[100];
  uint32_t int32Number = 600000000;
  
  sprintf(clockValue, "%d", int32Number); //convert uint_32 to String char[]
  printf("%s\n", clockValue);
}
```

### atoi()

Include in library **stdlib.h**.

```c
int atoi(const char *str)
```
Converts the string argument **str** to an integer (type int).  If no valid conversion could be performed, it **returns zero**.

**E.g**

```c
    char str[] = "C programming with GNU-GCC";
    int a = atoi(str);
    printf("%d \n", a);
```   

**Result**

```
0
```

```c
    char str[] = "1234";
    int a = atoi(str);
    printf("%d \n", a);
```

**Result**
``1234``   

### strncpy() 

Copy **n** character from **src** string to **dst** string.

```c
char *strncpy(char *dest, const char *src, size_t n)
```

**E.g**

```c
#include <stdio.h>      /* for printf() and fprintf() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */

int main() {
	char helloWorld[] = "Hello world 10 times";
    char dest[12];
    strncpy(dest, helloWorld, 2);
    printf("%s \n",dest);
}
```

```
He
```