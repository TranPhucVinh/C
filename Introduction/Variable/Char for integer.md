# ASCII code

**Decimal value**

```c    
printf("%c", 67); //C (Character 'C' has ASCII code 67)
```

**Hex value**

```c
printf("%c", 0x30);//0 (Character '0')
```

**ASCII code**

```c
printf("ASCII value: %d \n", ' ');//ASCII value: 32 
```

# char variable

Convert character to ASCII value: ``printf("b: %d \n", '6')``: ``b: 54``

```c
char c = 'a';  
printf("Character: %c ", c); //Character: a
```

```c
char c ='ab';
printf("Character %c ", c); //b (Only the last character is returned)
```

```c
char c = 8;
printf("Integer: %d ", c); //Integer: 8
```

```c
char c = 48;
printf("Character: %c ", c); //Character: 0
```

```c
char number = 128;
printf("number: %d ", number); //-128
```

**Explain**: As char is defined as signed char by default (1 byte of char includes 1 sign bit and 6 bits for storing number), so 128 has overflow 7 bit data, so it returns the signed number.

# unsigned char

``unsigned char`` is ``unint_8``

```c
unsigned char binVal0 = -3;
printf("%d \n", binVal0); //253 (1111 1101)
```

**Signed number** is operated by two's complement (bitwise then OR with bit 1).

3 = 0000 0011 => bitwise = 1111 1100
=> -3 = 1111 1100+1 = 1111 1101

```c
unsigned char signedNumber = -3000;
printf("%d \n", signedNumber); //72
unsigned char unsignedNumber = 3000;
printf("%d \n", unsignedNumber); //184
```

``72``: 0100 1000

As ``-3000`` is ``010001001000`` so bits after 8th bit is remove, so only ``01001000`` is left for ``72``

``3000``: ``101110111000``

``184`` is ``10111000``

**Example**

```c
#include <stdio.h>

int main (){
 	unsigned char varA = 19;
    unsigned char varB = -19;
    unsigned char varC = 256;
    printf("%d \n", varA);
    printf("%d \n", varB);
    printf("%d \n", varC);
}
```

**Result**

(warning when compile: warning: large integer implicitly truncated to unsigned type [-Woverflow])

```
varA: 19
varB: 237
varC: 0
```

# signed char

In GCC and G++, the default ``char`` type is ``signed char``.

```c
signed char varB = -19; //-19
```
