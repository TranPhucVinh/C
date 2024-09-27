# Change address of a pointer as a function argument

```c
#include <stdio.h>

int number1 = 9;
int number2 = 90;
int *pointer = &number1;

void changeValue (int *pptr);

int main () {
    printf("*pointer before %d \n", *pointer);
    changeValue(pointer);
    printf("*pointer after %d \n", *pointer);
}

void changeValue (int *pptr){
    pptr = &number2; //change pointing address of the argument pointer
}
```
**Output**
```
*pointer before 9
pointer after 9
```

**Problem solved**

```c
void changeValue (int *pptr){
    *pptr = number2;
}
```
**Output**
```
*pointer before 9
*pointer after 90
```
