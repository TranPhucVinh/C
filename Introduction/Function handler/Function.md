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

A function with no parameter can accept a void.

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

### Command Line Arguments with main()

```c
int main( int argc, char *argv[] ){}
```

It is possible to pass **some values** from the command line to your C programs when they are executed. These values are called **command line arguments** and many times they are important for your program especially when you want to control your program from outside **instead of hard coding** those values inside the code.

The command line arguments are handled using **main()** function arguments where ``argc`` refers to the **number of arguments** passed, and ``argv[]`` is a **pointer array** which points to **each argument** passed to the program.

```c
int main( int argc, char *argv[] )  {
      printf("The argument supplied is %s and total argument is %d \n", argv[0], argc);
}
```

Compile ``g++ -o test test.c``

``./test``

**Result**

```
The argument supplied is ./test and total argument is 1 
```
