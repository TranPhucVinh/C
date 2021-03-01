### Create function

```c
#include <stdio.h>

int addTwoNumbers(int a, int b){
    return a+b;
}

float addTwoFloatNumbers(float a, float b){
    return a+b;
}    

int main () {
    printf("Add 2 number: %d \n", addTwoNumbers(3, 4));
    printf("Add 2 number: %f \n", addTwoFloatNumbers(3.0, 4.0));
}
```

Short term function data type

```c
#include <stdio.h>

int add(int, int);

int main () {
   printf("%d\n", add(3,4)); //7
}

int add(int a, int b){
   return a+b;
}
```

### Local variable setup with {}

```c
#include <stdio.h>

int a = 20;
int main(int argc, char *argv[])
{
   {
      int a = 10;
      printf("%d \n", a); //10: local variable
   }
   printf("%d", a); //20: global variable
   return 0;
}
```

### Function arguments as void

A function with no parameter can accept a ``void``.

```c
#include <stdio.h>

int returnNumber(void){
   return 5;
}
int main () {
   printf("returnNumber: %d \n", returnNumber());

}
```
**Result**
```
returnNumber: 5
```

### Function overloading

C doesn't support function overloading as it is not an OOP language

This will give error

```c
int number(int a){
	return a;
}

int number(int a, int b){
	return a+b;
}

int main(){
    number(1);
    number(1, 2);
}
```

For function overloading information, check ``Function.md`` in ``Cplusplus\Introduction\OOP``.

### Command line arguments with main()

```c
int main( int argc, char *argv[] ){}
```

It is possible to pass some values from the command line to your C programs when they are executed. These values are called **command line arguments**.

* ``argc``: number of arguments passed
* ``argv[]``: pointer array which points to each argument passed to the program

**Example**

```c
#include <stdio.h>

int main(int argc, char *argv[])  {
    printf("argv[0]: %s \n", argv[0]);
    printf("argv[1]: %s \n", argv[1]);
    printf("Total argument: %d", argc);
}
```
**Input**: ``./a.out Hello``

**Output**

```
argv[0]: ./a.out 
argv[1]: Hello
Total argument: 2
```

**Example**: ``Rectangle calculation`` in ``Example projects\Intermediate.md``

To enter a string in ``*argv[]``, use ``\``:

**Input**: ``./a.out Hello,\ World !``

**Output**

```
argv[0]: ./a.out 
argv[1]: Hello, World !
Total argument: 2
```

### Variable Arguments

For **Variable Arguments** use, an ``int`` variable is required to represent the total number variable arguments passed.

**va_arg()**

```c
type va_arg(va_list ap, type)
```

* **ap**:  object of type ``va_list``
* **type**: type name

**Example**

```c
#include <stdio.h>
#include <stdarg.h> //for va_list, va_start(), va_end()

int sumIntNumbers(int num,...) {
   va_list valist;
   int sum;
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      sum += va_arg(valist, int);
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return sum;
}

int main() {
   printf("Sum of 2, 3, 4, 5 = %d\n", sumIntNumbers(4, 2, 3, 4, 5));
}   
```
