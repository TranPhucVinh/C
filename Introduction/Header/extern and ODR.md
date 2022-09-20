## One definition rule (ODR)

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
**Note**: This happens as mutiple sources like ``main.c``, ``head.c`` includes one ``head.h`` file. If the variable is defined in ``head.h`` and only one source calls it like ``main.c``, the ODR error doesn't happen (check ``Header file.md`` for that implementation).

### Problem solved

Solve the ODR issue by ``extern`` keyword:

``head.h``

```c
#include <stdio.h>
extern int a;
```
``head.c``
```c
#include "head.h"
int a = 10;
```
``main.c`` kept as above
