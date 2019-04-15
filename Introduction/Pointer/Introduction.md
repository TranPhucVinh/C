# Pointer

pointer: variable that stores address of other variable

*p: declare a pointer

*p : value at address

### Declare pointer variable

```c
int a;
int *p; //pointer to integer
char c;
char *p0; //pointer to character
double d;
double *p1; // pointer to double
const char *message1 = "Thread 1";
```

``%p``: is used for **pointer**, like ``%d`` for **int**, ``%s`` for **string**.

``&``: get the address of the variable

## Example

### Example 1

```c
p = &a //p is the address of a
printf("%p", &a);
```

### Example 2

```c
int a;
int *p;

a = 5;
p = &a; // p is address of variable a
```

As *p is the pointer that store the value at the address of a variable so that we can declare

```c
int *p = a; // they are both int value
int a = 6;
```

### Get value of pointer

**Program in C**

```c
int *p;
int a = 9;
int *pointer = &a;
int main(){
   p = &a;
   printf("pointer value %p \n", p);
   printf("address value of variable a %p \n", &a);
   printf("address of pointer variable %p \n", &p);
   printf("variable value %d \n", *p);
   printf("*& value is %d \n", *&a);
   printf("Value of variable pointer %p \n", pointer);
   printf("Value %d \n", *pointer);
   return(0);
}
```

**Result**

```
pointer value 0x601030 
address value of variable a 0x601030
address of pointer variable 0x601048
variable value 9
*& value is 9
Value of variable pointer 0x601030 
Value 9
```

We can also notice that

```c
*pointer = &a;
p = &a;
```

has returned the same value for ``p`` and ``pointer`` as the address of variable ``a``.

**Program in C++**

```c++
#include <iostream>

using namespace std;
int val =5;
int *p = &val;
main(){
	cout << "value: " << *p;
}
```

### scanf() with pointer

Prototype

``scanf()`` reads formatted input from stdin.

```c
int scanf(const char *format, ...)
```

**Explain**

```c
scanf("%d", &a);
```

To save the value of variable ``a``, we have to use ``&`` to get the address so that ``*&`` will return the value of variable a.