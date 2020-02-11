### malloc

```c
void *malloc(size_t size)
```

``malloc()`` returns a pointer to the allocated memory.

**String**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "Learn malloc");
   printf("String: %s \n", str);
}   
```

**Int**

```c
int *intPointer;

intPointer = (int *) malloc(1);
*intPointer = 12;
    
printf("Int value: %d", *intPointer); //12
```

### free()

```c
int *intPointer;

intPointer = (int *) malloc(1);
*intPointer = 12;
    
printf("Int value before: %d \n", *intPointer); //12
free(intPointer);
printf("Int value after: %d \n", *intPointer); //0
```