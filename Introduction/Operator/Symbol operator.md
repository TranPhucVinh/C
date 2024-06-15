# Comma (,) operator

Comma acts like a seperator within function calls and definitions, variable declarations and enum delcarations.

With ``()``, comma operator will start execution from left to right and returns the rightmost operand in the expression.

**Example 1**
```c
int a = (1, 2, 3);
printf("%d\n", a);//3
```
**Example 2**
```c
int a = (printf("%s\n", "Hello, World !"), 3);
printf("%d\n", a);
```
```
Hello, World !
3
```
**Example 3**
```c
int var, number;
number = (var=15, var+35);
printf("%d\n", number);//50
```

Comma operator is having the least precedence among all the operators available in C language.

```c
int a;
a = 1, 2, 3;
printf("%d\n", a);//1
```

This is equal to:

```c
int a;
(a=1), 4, 8;
```

# lvalue, rvalue

``lvalue``: left value, the value on the left is modificable, usually a variable.

``rvalue``: right value concept pulls or fetches the value of the expression or operand on the right side of the assignment operator. 

**E.g**
```c
int a = 6;
```

* ``a``: lvalue
* ``6``: rvalue

# := operator is not available in userspace and kernel GCC compiler

``:=`` is an assignment operator which is supported in just some programming language and tools.

``:=`` **is not available in userspace and kernel GCC compiler**.

This will give error on both userspace process and kernel module program:

```c
int a;
a := 12;
```

```
error: expected expression before ‘=’ token
7 |     a := 12;
```

``:=`` is available on [Makefile](https://github.com/TranPhucVinh/Linux-Shell/blob/master/Bash%20script/Build%20automation%20tools/Make/Fundamental%20concepts.md#operator), as it is equal to ``=``

# Symbols name

``;`` semicolon

``:`` colon

``-`` hyphen 

``—`` dash

``_`` underscore

``*`` asterisk

``()`` round bracket, bracket and parenthesis

``[]`` square brackets

``{}`` curly brackets, or braces.

``'`` apostrophe or single quote

``"`` double quote

``/`` slash

``\`` backlash. backlash doesn’t have a standard English meaning but is often used in various computing contexts.

* [#](https://github.com/TranPhucVinh/C/tree/master/Introduction/Macro#stringizing-operator-): tag, social hashtag, **stringizing operator**
