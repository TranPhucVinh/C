### char variable

```c
char c = 'a';  
printf("Character: %c ", c); //Character: a
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
char c ='ab';
printf("Character %c ", c); //b (Only the last character is returned)
```

Convert character to ASCII value: ``printf("b: %d \n", '6')``: ``b: 54``

### unsigned char

``unsigned char`` is ``unint_8``

```c
unsigned char binVal0 = -3;
printf("%d \n", binVal0);
```

``253`` (1111 1101)

**Signed number** is operated by two's implement (bitwise then OR with bit 1).

3 = 0000 0011 => bitwise = 1111 1100
=> -3 = 1111 1100+1 = 1111 1101

```c
unsigned char number = -3000;
printf("%d \n", number);
```

``72`` (0100 1000)

As ``-3000`` is ``010001001000`` so bits after 8th bit is remove, so only ``01001000`` is left for ``72``

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

### signed char

```c
signed char varB = -19; //-19
```
