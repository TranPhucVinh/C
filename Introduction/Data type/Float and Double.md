### Normally with negative number

```c
float y = -3.1;
printf("float number is: %f",y);
printf("size of negative float number is: %d", sizeof(y));
```
**Result**
```
float number is: -3.100000
size of negative float number is: 4
```

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
