### unsigned char

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