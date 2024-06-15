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
# Increment operator ++: ++i (prefix) and i++ (postfix)

``++i`` will increment the value of i, and then return the incremented value to ``j``

```c
int i,j;
j = ++i;
```

``j=1, i=1``


``i++`` will return its initial value first to ``j`` then increases its value

```c
int i,j;
j = i++;
```

``j=0, i=1``

```c
int x=5, y=7;
int z = x++ + ++y -8;
printf("x %d, y %d, z %d", x, y, z);//6 8 5
```
# Complement operator (~)
The complement operator ~ is a bitwise unary operator. It performs a bitwise NOT operation on its operand, which means it **inverts all the bits of the operand**.
```c
int binVal0 = 0b00;
int binResult = ~binVal0;
printf("%d \n", binVal0);   //0
printf("%d \n", binResult); //-1
```

**Explain**

```c
int binVal0 = 0b00;         //binVal0 = 0b 0000 0000;
int binResult = ~binVal0;   //binResult = 0b 1111 1111;
```

When converting back to integer, the duplicate 1 bit from the left is omit, and one bit is kept for sign. So, there is 2 bit left

```c
binResult = 0b11 = -1
```
Other decimal value
```c
int binVal0 = 5;
int binResult = ~binVal0;
printf("%d \n", binVal0);   //5
printf("%d \n", binResult); //-6 = 1111111111111010
```

## Complement unsigned char, unsigned int

```c
unsigned char binVal0 = 0b0;
unsigned char binResult = ~binVal0;
printf("%d \n", binResult); //255
```	

```c
unsigned int binVal0 = 0b0;
int binResult = ~binVal0;
printf("%d \n", binResult); //-1
```	
