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

### void pointer as function argument

```c
void display_string(void *a){
	printf("%s\n", a);
}

void display_int_number(void *a){
	printf("%d\n", a);
}

int main()
{  
	display_string("hello");//hello
	display_int_number(18);//18
}
```

This example is compiled normally with GCC. 

With G++, there will be error:

```
error: invalid conversion from ‘const void*’ to ‘void*’ [-fpermissive]
  display_string("hello");

error: invalid conversion from ‘int’ to ‘void*’ [-fpermissive]
  display_int_number(18);
```

**Problem solved**

```c
void display_string(void *a){
	printf("%s\n", (char*) a);
}

void display_int_number(void *a){
	printf("%d\n", *(int*) a);
}

int main()
{  
	char displayedString[] = "Hello, World !";
    int number = 18;
	display_string(displayedString);
    display_int_number(&number);
}
```

If passing ``display_string("Hello, World !")`` and ``display_int_number(18)``, there will be error:

```
error: invalid conversion from ‘const void*’ to ‘void*’ [-fpermissive]
  display_string("Hello, World !");

error: invalid conversion from ‘int’ to ‘void*’ [-fpermissive]
  display_int_number(18);
```