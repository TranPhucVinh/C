# Create function

## Create the very first function

```c
#include <stdio.h>

void display_string(){
   printf("Hello, World !\n");//Hello, World !
}

int main(){
   display_string();
}
```

## Function with arguments

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

## Function prototype

A **function prototype** or **function interface** is a declaration of a function that specifies the function’s name and type signature (data types of parameters, and return type), but omits the function body. 

```c
#include <stdio.h>

int addTwoNumbers(int a, int b);//This is function prototype

int main () {
    printf("Add 2 number: %d \n", addTwoNumbers(3, 4));
}

int addTwoNumbers(int a, int b){
    return a+b;
}
```

## Inner function

Inner function (also known as nested function) allows defining a function inside a function.

C and CPP only support declaring a function inside a function, not defining it.

This available with both GCC and G++:

```c
#include <stdio.h>

void display_string(){
   void inner_function();
   printf("Hello, World !\n");//Hello, World !
   inner_function();
}

int main(){
   display_string();
}

void inner_function(){
   printf("Don't call any inner");
}
```
Inner function method is applied in [callback by function pointer](Callback%20function.md#handle-callback-by-function-pointer) where the function pointer is declared inside the callback function.

## Short term function data type

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

## Get function name with ``__FUNCTION__``, ``__func__`` and ``__PRETTY_FUNCTION__``:

```c
void displayString(){
	printf("%s\n",  __FUNCTION__);//displayString
	printf("%s\n",  __func__);    //displayString
	printf("%s\n",  __PRETTY_FUNCTION__);//displayString
}
```

# Function arguments as void

A function with no parameter can accept a ``void``.

```c
#include <stdio.h>

int returnNumber(void){
   return 5;
}
int main () {
   printf("returnNumber: %d \n", returnNumber());//returnNumber: 5

}
```

# [Recursive function](Recursive%20function.md)
* [Use recursive to calculate the sum from 1 to n]()
* [Logarit can only be calculated by recursive]()
* [Hanoi tower]()
* [Raspbian device tree: Find all nodes with compatible string]()
* [Permutation]()
* [Combination]()
* [Check if an index existed inside a linked list]()

# Command line arguments with main()

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
    printf("argv[1][0]: %c \n", argv[1][0]);
    printf("Total argument: %d", argc);
}
```
**Input**: ``./a.out Hello``

**Output**

```
argv[0]: ./a.out 
argv[1]: Hello
argv[1][0]: H
Total argument: 2
```

To enter a string in ``*argv[]``, use ``\``:

**Input**: ``./a.out Hello,\ World\ !``

**Output**

```
argv[0]: ./a.out 
argv[1]: Hello, World !
Total argument: 2
```

**Application**: [Sum from 1 to n](https://github.com/TranPhucVinh/C/tree/master/Introduction/Examples#sum-from-1-to-n)

# Other concepts

* [Definition and Declaration](Definition%20and%20Declaration.md)
* [Conditional statements](Conditional%20statements.md)
* [Scope](Scope.md)
* [Callback function](Callback%20function.md)
* [Variable length argument](Variable%20length%20argument.md)
* [Random number generators](Random%20number.md)
