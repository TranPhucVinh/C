# Difference between variable declaration and definition

* Variable declaration : a variable is first declared or introduced before its first use.
* Variable definition: the variable is assigned a memory location and a value.

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

* [Bit operator](Bit%20operator.md)
* [Symbol operator](Symbol%20operator.md)
