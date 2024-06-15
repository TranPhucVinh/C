A bitwise operation operates on a bit string, a bit array or a binary numeral (considered as a bit string) at the level of its individual bits. Bitwise operators might be NOT, AND, OR, XOR,...

# Mask or bitmask

A mask or bitmask is data that is used for bitwise operations. Common bitmask functions are masking bits to 1, masking bits to 0, querying the status of a bit and toggling bit values.

Examples: 

Masking bits to ``1``

```
    10010101
 OR 11110000
  = 11110101
```

Masking bits to ``0``

```
    10010101
AND 00001111
  = 00000101
```

Querying the status of a bit

```
    10011101
AND 00001000
  = 00001000
```

# Bitwise OR |

```c
int binVal0 = 0b110;
int binVal1 = 0b111;
int binResult = binVal0 | binVal1;
printf("%d", binResult); //7 (0b111)
```

```c
int binVal0 = 0b11;
int binVal1 = 0b11;
int binResult = binVal0|binVal1;
printf("%d", binResult); //3
```
Compare the result with arithmetic operators addition +
```c
int binVal0 = 0b11;
int binVal1 = 0b11;
int binResult = binVal0+binVal1;
printf("%d", binResult); //6
```	

# Bitwise AND &

```c
int binVal0 = 0b110;
int binVal1 = 0b111;
int binResult = binVal0 & binVal1;
printf("%d", binResult); //6 (0b110)
```

# XOR operator (^)

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
Given ``binResult`` (``0b1111``) and ``binVal0`` (``0b1011``) with ``binResult = binVal0 ^ binVal1``, find ``binVal1``:
```c
binVal1 = binVal0 ^ binResult;
```
# Bit shifting

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

Any number left shift by 1 (``<< 1``) will be multiple by 2. E.g ``25 << 1 = 50``
