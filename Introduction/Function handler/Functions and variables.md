## Functions

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

Get function name with ``__FUNCTION__``, ``__func__`` and ``__PRETTY_FUNCTION__``:

```c
void displayString(){
	printf("%s\n",  __FUNCTION__);//displayString
	printf("%s\n",  __func__);    //displayString
	printf("%s\n",  __PRETTY_FUNCTION__);//displayString
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
   printf("returnNumber: %d \n", returnNumber());//returnNumber: 5

}
```

### Recursive function

Use recursive to calculate the sum from ``1`` to ``n``:

```c
#include <stdio.h>

int sum_of_numbers(int x);

int main()
{  
	int number = 20;
	printf("Sum from 1 to %d: %d", number, sum_of_numbers(number));
}

int sum_of_numbers(int number){
	if (number == 1) return 1;
	return number + sum_of_numbers(number - 1);
}
```

Application: [Hanoi tower](https://github.com/TranPhucVinh/C/blob/master/Introduction/Examples/Hanoi_tower.c)

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

## Variable

### Special character

```c
int _ = 9;
printf("_: %d\n", _);//9
```
```c
#include <stdio.h> 

int main(){ 
	int var = var;
	printf("var: %d\n", var);//var: 0
}
```
So this gives the same result:

```c
#include <stdio.h> 
int var = 9;
int main(){ 
	int var = var;
	printf("var: %d\n", var);//var: 0
}
```
