A static variable generally has [internal linkage](https://github.com/TranPhucVinh/C/blob/master/Introduction/Linkage.md#internal-linkage).

# Global static variable and static function

A global static variable and static function limit their scopes inside the source file it's declared.

In this example, local variable ``a`` and function ``display_string()`` limit its scope inside their source file ``head1.c`` and ``head2.c``. So when there will no error when those 2 files have the same variable name ``a`` and function ``display_string()``.

``head1.c``

```c
#include <stdio.h>

static int a = 123;
static void display_string(){
    printf("head1() called\n");
}

void head1(){
    display_string();
    printf("head1 a %d\n", a);
}
```

``head2.c``
```c
#include <stdio.h>

static int a = 456;
static void display_string(){
	printf("Display string in head2.c\n");
}

void head2(){
	display_string();
	printf("head2 a %d\n", a);
}
```
``main.c``
```c
#include <stdio.h>

void head1();
void head2();

int main() {
	head1();
	head2();
}
```

Compile ``g++ main.c head1.c head2.c``

**Result**

```
head1() called
head1 a 123
Display string in head2.c
head2 a 456
```

This method will allow reusing of the same function names and variables in other files.

CPP also supports [unnamed namespace](https://github.com/TranPhucVinh/Cplusplus/blob/master/Introduction/Function/Namespace.md#unnamed-namespace), an equivalent method to global static variable and static function.

# Global static and [ODR](https://github.com/TranPhucVinh/C/blob/master/Introduction/Header/README.md#one-definition-rule-odr)

``header.h``

```c
#include <stdio.h>
static int a = 10;

void address();
```
``header.c``
```c
#include "header.h"

void address() {
	printf("&a: 0x%p\n", &a);
}
```
``main.c``
```c
#include "header.h"

int main(){ 
    address(); // &a: 0x0x561d2e5fc014
    printf("&a: 0x%p\n", &a); // &a: 0x0x561d2e5fc010
}
```
Compile ``gcc main.c header.c`` normally and there will be no [ODR issue](https://github.com/TranPhucVinh/C/blob/master/Introduction/Header/README.md#one-definition-rule-odr).

For global static variable ``a`` in this case, it is included in two separate ``.c`` files, which result in two discrete copies of it so that there is no compilation error.

# Local static variable (variable inside function)

**Static variables** is used to created variable that are visible to only one function, but unlike local variables that get created and destroyed everytime a function is called, static variables do not lose their value between function calls.

```c
#include <stdio.h> 

int fun(){ 
  int static count = 0; 
  count++;
  return count; 
} 
   
int main(){ 
   printf("%d ", fun()); 
   printf("%d ", fun()); //count remains its value after 1st time call func()
   return 0; 
}
```

**Result**

``1 2``
