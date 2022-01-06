## Bitwise operator

A bitwise operation operates on a bit string, a bit array or a binary numeral (considered as a bit string) at the level of its individual bits. Bitwise operators might be NOT, AND, OR, XOR,...

## NOT operator !

```c
int a = 100;
int b = 0;
a = !a;
b = !b;
printf("a: %d, b: %d", a, b);//0, 1
```

## OR bit with | and +

```c
int binVal0 = 0b110;
int binVal1 = 0b111;
int binResult = binVal0 | binVal1;
printf("%d", binResult); //7 (0b111)
```

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

## AND operator (``&``)

```c
int binVal0 = 0b110;
int binVal1 = 0b111;
int binResult = binVal0 & binVal1;
printf("%d", binResult); //6 (0b110)
```

## XOR operator (^)

```
0^0=0
1^1=0
1^0=1
```

```c
int binVal0 = 0b1011;
int binVal1 = 0b0100;
int binResult = binVal0 ^ binVal1; //0b1111
```

### Bit shifting

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

## Complement operator (~)

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

### Complement unsigned char, unsigned int

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
