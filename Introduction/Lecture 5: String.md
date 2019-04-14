### sprintf()

Composes a string with the same text that would be printed if format was used on printf, but instead of being printed, the content is stored as a C string in the **buffer** pointed by **str**.

```c
/* sprintf example */
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