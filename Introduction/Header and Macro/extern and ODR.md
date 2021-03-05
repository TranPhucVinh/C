### One definition rule (ODR)

``head.h``

```c
#include <stdio.h>

int a = 10;
```
``head.c``
```c
#include "head.h"
```

``main.c``

```c
#include "head.h"

int main(){
	printf("%d \n", a);
}
```

**Error**: 

```
/usr/bin/ld: /tmp/cc27NLmt.o:(.data+0x0): multiple definition of `a'; /tmp/ccZ06TNs.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status
```

### String display with extern to fit ODR

``head.h``
```c
#include <stdio.h>

extern char displayedString1[], displayedString2[];
```

``head.c``
```c
#include "head.h"

char displayedString1[] = "Hello, World String 1";
char displayedString2[] = "Hello, World String 2";
```

``main.c``
```c
#include "head.h"

int main(){
	puts(displayedString1);
	puts(displayedString2);
}
```