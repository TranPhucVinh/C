If there is no further notice, all source codes below are implemented on Unix:

## Non-support garbage collection causes unexpected scoping call result

In this example, we get the address of local variable ``a`` inside ``declare_function()``. Outside this function, ``a`` is not available for sure and we expect its register doesn't store its value.

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

That happen as C doesn't support garbage collection. Although outside ``declare_function()``, local variable ``a`` can't be access, the register address that was allocated for it still keeps its value.

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
	printf("*reg_2 outside: %d\n", *reg_1);

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
*reg_2 outside: 123
reg_1 reg_2: 0x7ffccbea0554 0x7ffccbea0554
*reg_1 *reg_2: 456 456
```

In this example, as ``reg_2`` is not intended to effect ``reg_1`` but it is called in ``call_function_2()`` after ``call_function_1()`` so it will override ``reg_1`` value.

As being overrided, after that call ``reg_1`` and ``reg_2`` will also have the same address.

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
