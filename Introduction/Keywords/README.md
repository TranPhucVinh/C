# Available keywords

* [const](#const)
* [auto](#auto)
* [extern](https://github.com/TranPhucVinh/C/tree/master/Introduction/Keywords#extern)
* [inline](https://github.com/TranPhucVinh/C/blob/master/Introduction/Keywords/inline.md)
* [static](https://github.com/TranPhucVinh/C/blob/master/Introduction/Keywords/static.md)
* [typedef](https://github.com/TranPhucVinh/C/blob/master/Introduction/Keywords/typedef.md)
* [volatile](https://github.com/TranPhucVinh/C/blob/master/Introduction/Keywords/volatile.md)

# const

``const`` is used to define constant variable and can't be changed

E.g: ``const int a = 19``

To change ``const`` variable: Use pointer, check [example Change value of a variable with pointer](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Pointer/Implementations.md#change-value-of-a-variable-with-pointer)

``const`` can be local variable:

```c
#include <stdio.h>

int const_test(int a){
    const int b = a;
    return b;
}

int main() {
    printf("%d\n", const_test(1));// 1
    printf("%d\n", const_test(2));// 2
    printf("%d\n", const_test(3));// 3
}
```

## const as function definition

Using ``const`` in function doesn't effect its definition:

```c
#include <stdio.h> 

const int function(int a){
    a += 1;
    return a;
}

int main() 
{ 
    int b = function(123);
    printf("%d\n", b);
    b += 19;
    printf("%d\n", b);
    return 0; 
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
        printf("Value of global x is %d\n", x);//50
    }
    printf("Value of local x is %d\n", x);//10
    return 0;
}
```
**Note**
Must have ``{}``, without ``{}`` there will be error 

```
error: extern declaration of ‘x’ follows declaration with no linkage
         extern int x;
```

For extern implementation with header files, check [header document](https://github.com/TranPhucVinh/C/tree/master/Introduction/Header).
