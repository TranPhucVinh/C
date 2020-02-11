### Pointers to void

A pointer of type void (e.g ``void *pointerName``) represents the address of an object,  but not its type.

```c
#include <stdio.h>

int main () {
   int a = 0;
   void *pointer = &a;
   (void) pointer; //this line can be commented and will give the same result
   printf("Value *(int *)pointer is: %d \n", *(int *)pointer);
   // printf("Value *pointer is: %d \n", *pointer);
   printf("Value pointer is: %d \n", pointer);
}
```
**Result**
```
Value *(int *)pointer is: 0
Value pointer is: 6487620
```

### Error

```c
#include <stdio.h>

void *pointer;

int main () {
   int a = 0;
   *pointer = &a;
    [...]
}
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
