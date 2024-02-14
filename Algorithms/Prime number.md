# Find all prime numbers less than a given integer value

**Best approach**: A prime number isn't divisible to any number less than its square root.

```c
#include <stdio.h>
#include <math.h>

#define NUMBER 100

int main () {
    for (int i = 1; i <= NUMBER; i++)
    {
        int total_divisor = 0;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if ((i % j) == 0) total_divisor++;
        }
        if (total_divisor == 0) {
            printf("%d ", i);
        }
    }
}
```
**Naive approach**:
```c
#include <stdio.h>

#define NUMBER 100

int main () {
    for (int i = 1; i <= NUMBER; i++)
    {
		int total_divisor = 0;
        for (int j = 1; j <= i; j++)
        {
            if ((i % j) == 0) total_divisor++;
        }
        if (total_divisor == 2) printf("%d ", i);
    }
}
```
# Find all natural numbers, which is less than a given N, to have only 3 divisors
From prime number, we have a lemma: **Numbers with only 3 divisors are square numbers of prime numbers**
```c
#include <stdio.h>
#include <math.h>

#define NUMBER 123

void list_primes(int range){
    for (int i = 1; i <= range; i++)
    {
        int total_divisor = 0;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if ((i % j) == 0) total_divisor++;
        }
        if (total_divisor == 0) {
            printf("%d ", i*i);
        }
    }
}

int main () {
    int range = sqrt(NUMBER);
    list_primes(range);
}
```
