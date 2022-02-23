# const

``const`` is used to define constant variable and can't be changed

E.g: ``const int a = 19``

To change ``const`` variable: ``Pointer/Examples.md`` -> ``Example 1.3: Change value of a variable with pointer``

Local ``const`` variable inside a function is fine and gives no issue:

```c
#include <stdio.h>

int const_test(int a){
    const int b = a;
    return b;
}

int main(int argc, char *argv[]) {
    printf("%d\n", const_test(1));//1
    printf("%d\n", const_test(2));//2
    printf("%d\n", const_test(3));//3
}
```

# auto

``auto`` is used to defined local variable

```c
void printFunction(){
	int auto a = 19;
	printf("%d ", a);
}
```
# extern

``extern`` variables are also known as global variables, they are variables defined outside any function block. 

Access global variable if there is a local variable with same name:

```c
int x = 50; // Global x
 
int main()
{
    int x = 10; // Local x
    {
        extern int x;
        printf("Value of global x is %d\n", x);
    }
    printf("Value of local x is %d\n", x);
    return 0;
}
```
**Note**
Must have ``{}``, without ``{}`` there will be error 

```
error: extern declaration of ‘x’ follows declaration with no linkage
         extern int x;
```