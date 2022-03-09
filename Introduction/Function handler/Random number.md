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

Generate a float random number from range:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER 	35
#define UPPER	40

void generate_random_number(float lower, float upper)
{
	float number = (float)rand()/(float)(RAND_MAX) * (upper- lower) + lower;
	printf("%f", number);
}
  
// Driver code
int main()
{ 
    srand(time(0));
  
    generate_random_number(LOWER, UPPER);
  
    return 0;
}
```
