# Change variable address by pointer as function argument

```c
#include <stdio.h>

int a = 8;
int b = 10;

void foo(int *ptr)
{
	ptr = &a;
}

int main()
{
	int* ptr;
	ptr = &b;
	printf("*ptr: %d", *ptr);//10
	foo(ptr);
	printf("*ptr: %d", *ptr);//10, expected 8
	return 0;
}
```
We expect ``ptr`` to store the address value of ``a`` but ``ptr`` passed to ``foo()`` is the value of ``ptr`` (i.e ``&b``).

That happens because the pointer ptr in ``foo()`` is a local copy of the pointer you passed in main. When you do ``ptr = &a``, you change this local copy to point to a, but the original pointer in main (ptr in main) remains unchanged.

**Problem solved**: 

Use ``memcpy()``

```c
void foo(int *ptr)
{
	memcpy(ptr, &a, sizeof(int));
}

int main()
{
	int* ptr;
	ptr = &b;
	printf("*ptr: %d", *ptr);//10
	foo(ptr);
	printf("*ptr: %d", *ptr);//8
	return 0;
}
```
Use double pointer
```c
void foo(int **ptr) {
    *ptr = &a;  // Dereference the pointer to pointer and change the original pointer
}

int main() {
    int* ptr;
    ptr = &b;
    printf("*ptr: %d\n", *ptr); // 10
    foo(&ptr);                  // Pass the address of ptr
    printf("*ptr: %d\n", *ptr); // 8, now ptr points to 'a'
    return 0;
}
```

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
