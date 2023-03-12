# Definition and Declaration

* Variable declaration : a variable is first declared or introduced before its first use.
* Variable definition: the variable is assigned a memory location and a value.

**Declaration** of a variable is for informing to the compiler the following information: name of the variable, type of value it holds and the initial value if any it takes. i.e., declaration gives details about the properties of a variable. 

**Definition** of a variable says where the variable gets stored. i.e., memory for the variable is allocated during the definition of the variable.

In C language definition and declaration for a variable takes place at the same time. i.e. there is no difference between declaration and definition

```c
//This is considered as both declaration and definition
int a;
```

If we want to only declare variables and not to define it i.e. we do not want to allocate memory, then ``extern`` can be used:

```c
extern int a;
```

With ``extern``, only the information about the variable is sent and no memory allocation is done. This tells the compiler that the variable a is declared now while memory for it will be defined later in the same file or in different file. For examples and specific implementations with extern, check [its document in Header folder](../Header/)

Declaration of a function provides the compiler the name of the function, the number and type of arguments it takes and its return type. 

For example:

```c
//function add() is declared here
int add(int, int);

//Other operations go here

//Now, function add() is defined
int add(int a, int b)
{
  return (a+b);
}
```

# Define variables

Must not define by this way:

```c
#include <stdio.h>

int number;

number = 9;

int main(){
	printf("number: %d \n", number);
}
```

This gives warning in GCC and gives error in G++.

Error: 

```
error: 'number' does not name a type
 number = 9;
 ^
```

# Special character

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

# Operators

## [Bit operator](Bit%20operator.md)

* [Bitwise operator]()
* [Mask or bitmask]()
* [NOT operator !]()
* [OR bit with | and +]()
* [AND operator &]()
* [XOR operator (^)]()
* [Bit shifting]()
* [Complement operator (~)]()

## [Symbol operator](Symbol%20operator.md)

* [:=]()