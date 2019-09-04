``memcpy()`` copies n characters from memory area str2 to memory area str1.

```c
void *memcpy(void *str1, const void *str2, size_t n)
```

**Example**

```c
#include <stdio.h>
#include <string.h>

int main () {
   const char src[50] = "http://www.tutorialspoint.com";
   char dest[50];
   strcpy(dest,"Heloooo!!");
   printf("Before memcpy dest = %s\n", dest);
   memcpy(dest, src, strlen(src)+1);
   printf("After memcpy dest = %s\n", dest);
   
   return(0);
}
```
**Result**
```
Before memcpy dest = Heloooo!!
After memcpy dest = http://www.tutorialspoint.com
```