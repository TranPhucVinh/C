# String

### sprintf()

Composes a string with the same text that would be printed if format was used on printf, but instead of being printed, the content is stored as a C string in the **buffer** pointed by **str**.

```c
#include <stdio.h>

int main ()
{
  char buffer [50];
  int n, a=5, b=3;
  n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
  printf ("[%s] is a string %d chars long\n",buffer,n);
  return 0;
}
```

```
[5 plus 3 is 8] is a string 13 chars long
```

### memset()

Include in library **string.h**.

``memset()`` copies the character **c** (an unsigned char) to the first **n** characters of the string pointed to, by the argument **str**.

**Prototype**

```c
void *memset(void *str, int c, size_t n)
```

```c
int main(){
	char str[] = "C programming with GNU-GCC";
    memset(str,'$',7);
    puts(str);
}
```

**Result**

```
$$$$$$$amming with GNU-GCC
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
``0``

```c
    char str[] = "1234";
    int a = atoi(str);
    printf("%d \n", a);
```
**Result**
``1234``    