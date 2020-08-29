### Pointers to void

A pointer of type void (e.g ``void *pointerName``) represents the address of an object,  but not its type. With ``void*``, you can cast the type of this pointer to any other type.

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
```
test.c:7:5: error: 'void*' is not a pointer-to-object type
    *pointer = &a;
```
**Solve**

```c
void *pointer;
int a = 0;
pointer = &a;
```

### Error

```c
printf("Value *pointer is: %d \n", *pointer);
```

```
test.c:8:40: error: 'void*' is not a pointer-to-object type
    printf("Value *pointer is: %d \n", *pointer);
```

### Casting pointer void to char

```c
char *hw = "Hello, World!";
void *pointer;
pointer = hw;
   
printf("Char value is: %s \n", pointer); //Hello, World!
```

### Pointer of pointer

```c
int number1 = 9;

int *ptr = &number1;
int **pptr = &ptr;

int main(){
  printf("ptr: %p \n", ptr);
  printf("pptr: %p \n", pptr);
  printf("**pptr: %d \n", **pptr); //9
}
```