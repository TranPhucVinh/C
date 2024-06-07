Unary operators are the operators that perform operations on **a single operand** to produce a new value.

# Minus operator
```c
int a = 10;
int b = -a;  // b = -10
```
The **subtraction operator** and **the minus operator** refer to the same symbol - but are used in different contexts.

# NOT operator !

Change the whole value from ``0`` to ``1`` and ``diffrent from 0`` to ``0``:

```c
int a = 100;
int b = 0;
a = !a;
b = !b;
printf("a: %d, b: %d", a, b);//0, 1
```
