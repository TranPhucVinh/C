# Pointer

pointer: variable that stores address of other variable

``*p``: declare a pointer

``*p``: value at address

All the pointer syntax works the same in both C/C++.

### Declare pointer variable

```c
int *p; //pointer to integer
char *p0; //pointer to character
double *p1; // pointer to double
const char *message1 = "Thread 1";

int* intPointer; //Equal to the previous ways and will give the same result
```

``&``: get the address of the variable

``%p``: is used to print ouf the hex value.

```c
int a = 11;
printf("%p", a); //0xb
```

## Example

### Example 1

```c
p = &a //p is the address of a
printf("%p", &a);
```

**Note**: ``*&a`` is ``a``.

### Example 2

```c
int a;
int *p;

a = 5;
p = &a; // p is address of variable a
```

### Example 3: Change value of a variable with pointer

```cpp
int value = 10;
printf("before %d \n", value); //10
int *ptr = &value;
*ptr = 90;
printf("after %d \n", value); //90
```

This way also work with ``const`` variable (using ``gcc`` compiler)

```cpp
const int value = 32;
int *ptr = &value;
*ptr = 0;
```

### Get value of pointer

```c
int *p;
int a = 9;
int *pointer = &a; //Declare a pointer name pointer with the address of variable a
int main(){
   p = &a;
   printf("pointer value %p \n", p); //0x601030
   printf("address value of variable a %p \n", &a); //0x601030
   printf("address of pointer variable %p \n", &p); //0x601048
   printf("Value of variable pointer %p \n", pointer); //0x601030
   printf("variable value %d \n", *p); //9
   printf("*& value is %d \n", *&a); //9
   printf("Value *pointer is %d \n", *pointer); //9
   return(0);
}
```

We can also notice that

```c
*pointer = &a;
p = &a;
```

has returned the same value for ``p`` and ``pointer`` as the address of variable ``a``.

### ``sizeof()``

In 64-bit computer

```c
int a;
sizeof(&a); //8
```

```c
char *test = "1";
printf("%d", sizeof(test)); //8
```

``sizeof(&a)`` and ``sizeof(test)`` are 8 byte they store the 64-bit address.

To get size of a string point by ``char*``, use ``strlen()``

```c
char *test = "123";
strlen(test)); //3
```