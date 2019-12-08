### char variable

Can store **character** or **integer value**

```c
// character
char c;
c = 'a';
printf("Character %c ", c);
```

```c
// integer
char c;
c = 8;
printf("Integer %d ", c);
```

### char vs value in ASCII code

```c
printf("b: %d \n", '6');	
```

**Result**: 54

### Notes

``char c ='ab'`` => Warning "character constant too long for its type" => **WRONG**

So, **char** in C go only with one word.

### unsigned char

``unsigned char`` is ``unint_8``

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

### char

```c
char varB = -19; //-19
```
