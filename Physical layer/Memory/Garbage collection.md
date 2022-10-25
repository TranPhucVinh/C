If there is no further notice, all source codes below are implemented on Unix:

## Non-support garbage collection causes unexpected scoping call result

In this example, we get the address of local variable ``a`` (stored in stack segment) inside ``declare_function()``. Outside this function, ``a`` is not available for sure and we expect its register doesn't store its value.

```c
#include <stdio.h>

int *get_reg;
void declare_function();

int main() 
{ 
	declare_function();
  	printf("get_reg outside declare_function(): %p\n", get_reg);
	printf("*get_reg outside: %d\n", *get_reg);

	return 0; 
} 

void declare_function(){
	int a = 10;
	get_reg = &a;
	printf("get_reg inside declare_function(): %p\n", get_reg);
	printf("*get_reg inside: %d\n", *get_reg);
}
```

**Result**

```
get_reg inside declare_function(): 0x7ffc788f1994
*get_reg inside: 10
get_reg outside declare_function(): 0x7ffc788f1994
*get_reg outside: 10
```

While we expect:

```
(just expectation)
get_reg inside declare_function(): 0x7ffc788f1994
*get_reg inside: 10
get_reg outside declare_function(): 0x7ffc788f1994
*get_reg outside: 0
```

That happen as C and CPP (compiled this program with both GCC/G++ with ``.c`` and ``cpp`` still gives the same result) doesn't support garbage collection. Although outside ``declare_function()``, local variable ``a`` can't be access, the register address that was allocated for it still keeps its value.

### Accessing address of local variables is a bad practice and must not be implemented

Accessing address of local variables will result in unexpected behavior so that it must not be implemented. Take this example:

```c
#include <stdio.h>
#include <stdlib.h>

int *get_reg;
void declare_function();
void function();

int main() 
{ 
	declare_function();
  	printf("get_reg outside declare_function(): %p\n", get_reg);
	printf("*get_reg outside: %d\n", *get_reg);

	function();

	printf("get_reg outside declare_function(): %p\n", get_reg);
	printf("*get_reg outside: 0x%x\n", *get_reg);
	
	return 0; 
} 

void declare_function(){
	int a = 12;
	get_reg = &a;
	printf("get_reg inside declare_function(): %p\n", get_reg);
	printf("*get_reg inside: %d\n", *get_reg);
}

void function(){
	int b_1 = 0x34;
	// printf("&b_1: %p\n", &b_1);
	int b_2 = 0x56;
	// printf("&b_2: %p\n", &b_2);
}
```

**Result**

```
get_reg inside declare_function(): 0x7fffa5c2b704
*get_reg inside: 12
get_reg outside declare_function(): 0x7fffa5c2b704
*get_reg outside: 12
get_reg outside declare_function(): 0x7fffa5c2b704
*get_reg outside: 0xc
```

We can see that ``0xc`` is an unexpected variable. If enabling ``printf()`` in ``function()`` like this:

```c
void function(){
	int b_1 = 0x34;
	printf("&b_1: %p\n", &b_1);
	int b_2 = 0x56;
	printf("&b_2: %p\n", &b_2);
}
```

**Result**

```
get_reg inside declare_function(): 0x7ffdc2ea6574
*get_reg inside: 12
get_reg outside declare_function(): 0x7ffdc2ea6574
*get_reg outside: 12
&b_1: 0x7ffdc2ea6570
&b_2: 0x7ffdc2ea6574
get_reg outside declare_function(): 0x7ffdc2ea6574
*get_reg outside: 0x56
```

## Non-supported garbage collection effected by override pointer setup

When local variable getting out of scope, its register address will hold its value until some other variable declared in some sibling block variable overrides it.

```c
#include <stdio.h>

int *reg_1, *reg_2;
void call_function_1();
void call_function_2();

int main() 
{ 
	call_function_1();
  	printf("reg_1 outside call_function_1(): %p\n", reg_1);
	printf("*reg_1 outside: %d\n", *reg_1);

	call_function_2();
	printf("reg_1 reg_2: %p %p\n", reg_1, reg_2);
	printf("*reg_1 *reg_2: %d %d\n", *reg_1, *reg_2);
	return 0; 
} 

void call_function_1(){
	int a = 123;
	reg_1 = &a;
	printf("reg_1 inside call_function_1(): %p\n", reg_1);
	printf("*reg_1 inside: %d\n", *reg_1);
}

void call_function_2(){
	/*
		Simply set value for reg_2, a dummy pointer,
		but that will effect reg_1
	*/
	int b = 456;
	reg_2 = &b;
}
```

**Result**

```
reg_1 inside call_function_1(): 0x7ffccbea0554
*reg_1 inside: 123
reg_1 outside call_function_1(): 0x7ffccbea0554
*reg_1 outside: 123
reg_1 reg_2: 0x7ffccbea0554 0x7ffccbea0554
*reg_1 *reg_2: 456 456
```

In this example, as ``reg_2`` is not intended to effect ``reg_1`` but it is called in ``call_function_2()`` after ``call_function_1()`` so it will override ``reg_1`` value.

As being overrided, after that call ``reg_1`` and ``reg_2`` will also have the same address.

## Garbage collection is effected by malloc() usage

```c
int main() 
{ 
	declare_function();
  	printf("get_reg outside declare_function(): %p\n", get_reg);
	printf("*get_reg outside: %d\n", *get_reg);

	int *b = malloc(1);
	free(b);

	printf("get_reg outside declare_function(): %p\n", get_reg);
	printf("*get_reg outside: %d\n", *get_reg);
	
	return 0; 
} 
```

**Result**

```
get_reg inside declare_function(): 0x7fff40033594
*get_reg inside: 12
get_reg outside declare_function(): 0x7fff40033594
*get_reg outside: 12
get_reg outside declare_function(): 0x7fff40033594
*get_reg outside: 32767 (garbage value)
```

As noted in **Accessing address of local variables is a bad practice and must not be implemented**, this method to access local variable is a bad practice so the behavior of this program might not need explanation. This program behavior varies in multiple platform, like ESP-IDF as ESP-IDF supports garbage collection. Check the corresponding example in ESP-IDF for this program implementation.

## Issue doesn't happen on Windows

With source code above, if compiling and running them on Windows Git Bash, the result will be:

```
get_reg inside declare_function(): 000000000062FDEC
*get_reg inside: 10
get_reg outside declare_function(): 000000000062FDEC
*get_reg outside: 0
```

And 

```
reg_1 inside call_function_1(): 000000000062FDEC
*reg_1 inside: 123
reg_1 outside call_function_1(): 000000000062FDEC
*reg_2 outside: 0
reg_1 reg_2: 000000000062FDEC 000000000062FDEC
*reg_1 *reg_2: 0 0
```
