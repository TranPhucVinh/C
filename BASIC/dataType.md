### float and double

**double** can also be declared as **long float**.

```
float -> %f

double -> %lf
```

### static

**static:** local variable but the value remain unchanged in a function

### size_t

size_t is actually unsigned int

typedef unsigned int size_t;

so if the value of variable with size_t is negative, the result will be unpredictable

```c
#include <iostream>

using namespace std;

int main() {
    size_t a = 0;
    cout << a-2 << endl;
    return 0;
}
```

**Result** ``18446744073709551614``
