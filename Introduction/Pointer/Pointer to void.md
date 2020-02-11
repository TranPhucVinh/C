### Pointers to void

A pointer of type void (e.g ``void *pointerName``) represents the address of an object,  but not its type.

```c
#include <stdio.h>

int main () {
   int a = 12;
   void *pointer = &a;
   
   printf("Value *(int *)pointer is: %d \n", *(int *)pointer); //12
   printf("Value (int *)pointer is: %p \n", (int *)pointer); //0x7fff1f05ed4c
   printf("Value pointer is: %p \n", pointer); //0x7fff1f05ed4c
}
```

### Error

```c
void *pointer;
int a = 0;
*pointer = &a;
```
**Error**
```
test.c:7:5: error: 'void*' is not a pointer-to-object type
    *pointer = &a;
```

```c
printf("Value *pointer is: %d \n", *pointer);
```

**Error**
```
test.c:8:40: error: 'void*' is not a pointer-to-object type
    printf("Value *pointer is: %d \n", *pointer);
```