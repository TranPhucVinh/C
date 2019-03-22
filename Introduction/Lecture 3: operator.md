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

### Binary and Operator

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