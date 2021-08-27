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
   printf("returnNumber: %d \n", returnNumber());//returnNumber: 5

}
```

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