### malloc

```c
void *malloc(size_t size)
```

``malloc()`` returns a pointer to the allocated memory

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "Learn malloc");
   printf("String = %s \n", str);
}   
```