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
# Integer factorization
A **trial division method** is a common algorithm for integer factorization
```cpp
std::vector<int> factorize(int n) {
    std::vector<int> factors;

    if (n == 1) {
        factors.push_back(1);
        return factors;
    }

    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    // If n is a prime number greater than 1
    if (n > 1) {
        factors.push_back(n);
    }

    return factors;
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
