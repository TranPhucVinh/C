``rand()`` and ``srand()`` are defined in ``stdlib.h``

Generate a random number

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Random number %d\n", rand());
    return(0);
}
```

Then the same random number will be generated every time we run the program.

To generate a new number every time:

```c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));
    printf("Random number %d\n", rand());
    return(0);
}
```