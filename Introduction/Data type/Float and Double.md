### float and double

**double** can also be declared as **long float**.

```
float -> %f

double -> %lf
```

### Comparing float and double

```c
#include <stdio.h>
void main() {
	double x = 3.1;
	float y = 3.1;
	if (x == y){
		printf("Yes\n");
	}
	else {
		printf("No\n");
	}
}
```

**Result**

```
No
```
