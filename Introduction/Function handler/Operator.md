# operator

### OR bit (``|``)

```c
int binVal0 = 0b110;
int binVal1 = 0b111;
int binResult = binVal0 | binVal1;
printf("%d", binResult); //7 (0b111)
```

### AND bit (``&``)

```c
int binVal0 = 0b110;
int binVal1 = 0b111;
int binResult = binVal0 & binVal1;
printf("%d", binResult); //6 (0b110)
```

### Bitwise

| Operator |7|6|5|4|3|2|1|0|Value|
| ------- |--|--|--|--|--|--|--|--|--|
|A |0|0|0|1|1|0|0|0|24|		
|A >> 1 |0|0|0|0|1|1|0|0|12|			
|A >> 2 |0|0|0|0|0|1|1|0|6|
|A << 3	|1|1|0|0|0|0|0|0|192|
|A >> 4	|0|0|0|0|0|0|0|1|1 (lost the last bit)| 

```c
shift = shift << 1;
```
can be written as
```c
shift <<= 1;
```

## Binary and Operator

### OR and ``+``

```c
int binVal0 = 0b11;
int binVal1 = 0b11;
int binResult = binVal0+binVal1;
printf("%d", binResult); //6
```	

```c
int binVal0 = 0b11;
int binVal1 = 0b11;
int binResult = binVal0|binVal1;
printf("%d", binResult); //3
```

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

### How it works ?

```c
int binVal0 = 0b00; //binVal0 = 0b 0000 0000;
int binResult = ~binVal0; //binResult = 0b 1111 1111;
```

When converting back to integer, the duplicate 1 bit from the left is omit, and one bit is kept for sign. So, there is 2 bit left

```c
binResult = 0b11 = -1
```

### bitwise unsigned char, unsigned int

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

## lvalue, rvalue

``lvale``: left value, the value on the left is modificable, usually a variable.

``rvalue``: Rvalue concept pulls or fetches the value of the expression or operand on the right side of the assignment operator. 

can't use ``PB5 = PB5^1;`` as PB5 is a macro, not variable

## The difference between ``++i`` and ``i++``

``++i`` will increment the value of i, and then return the incremented value to ``j``

```c
int i,j;
j = i++;
```

``j=1, i=1``

``i++`` will return its initial value firt to ``j`` then increases its value

```c
int i,j;
j = ++i;
```

``j=0, i=1``
