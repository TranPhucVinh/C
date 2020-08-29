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
**Input** ``./a.out Hello``

**Output**

```
argv[0]: ./a.out 
argv[1]: Hello
Total argument: 4
```