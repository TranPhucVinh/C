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

**Result**: ``No``

## Problem with typecast

### Unable to get the int value

```c
int a = (float) 12;
int b = 1;
printf("%lf %lf\n", a, b);//0.0 0.0
```
**Problem solve**

```c
int a = 12;
int b = 1;
printf("%lf %lf\n", (float) a, (float) b);//12.0 1.0
```
### Wrong calculation

```c
int a = 1;
int b = 70;
float c = (float) ((a*16*16+b)/10);
printf("%lf\n", c);//32.0; expected 32.6
```
**Problem solve**

```c
int a = 1;
int b = 70;
float c = ((float)a*16*16+ (float) b)/10;
printf("%lf\n", c);//32.5999
```