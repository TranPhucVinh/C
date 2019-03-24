# operator

| OR bit

A = 0011 1100

B = 0000 1101

A|B = 0011 1101

bitwise

![](bitwise.png)

```c
shift = shift << 1;
```
can be written as
```c
shift <<= 1;
```

## Binary and Operator

### OR and +

```c
	int binVal0 = 0b11;
	int binVal1 = 0b11;
	int binResult = binVal0+binVal1;
	printf("%d", binResult);
```	
**Result** ``6``

```c
	int binVal0 = 0b11;
	int binVal1 = 0b11;
	int binResult = binVal0|binVal1;
	printf("%d", binResult);
```
**Result** ``3``

### bitwise

```c
	int binVal0 = 0b00;
	int binResult = ~binVal0;
	printf("%d \n", binVal0);
	printf("%d \n", binResult);
```

```
0 
-1 
```

The same result for 

```c
	char binVal0 = 0b00;
	char binResult = ~binVal0;
```

## lvalue, rvalue

``lvale``: left value, the value on the left is modificable, usually a variable.

``rvalue``: Rvalue concept pulls or fetches the value of the expression or operand on the right side of the assignment operator. 

can't use ``PB5 = PB5^1;`` as PB5 is a macro, not variable
