# float

Limit float dgigit to 2 number
```c
printf("float number is: %.2f",y);
```

## Check if a float variable is an int variable

```c
#include <stdio.h>
#include <unistd.h>

int checkInteger(float floatNum){
    int intNum = floatNum;

    float remainder = floatNum - intNum;

    if (remainder > 0) {
		printf("Number is not integer\n");
        return 0;//If not int number, return 0
    }
    return intNum;
}

int main(int argc, char *argv[])  {
	printf("%d\n", checkInteger(1.4));
	printf("%d\n", checkInteger(12.0));
}
```

## / arithemtic for float number

```c
float number = 2/3;
printf("%.2f", number);//0.0
```
Problem solved:
```c
float number = 2.0f/3.0f;
printf("%.2f", number);//0.67
```

Or

```c
float number = (float) 2/3;
printf("%.2f", number);
```

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
## Convert string to float

```c
strtof(const char* str, char **endptr);
```

```c
#include <stdio.h>
#include <stdlib.h> //For strtof()

int main()
{
     char array[] = "34.56 8.91 123.45";
    char *pend;

    float f1 = strtof(array, &pend);
    float f2 = strtof(pend, &pend);
    float f3 = strtof(pend, NULL);
    printf("f1: %.2f, f2: %.2f f3: %.2f\n", f1, f2, f3);
    
    float f4 = strtof("12.34", NULL);
    printf("f4: %.2f\n", f1);//12.34
}
```

## Floating-point remainder

``%`` operator is not used for float number

``fmod``, ``fmodf``, ``fmodl``: floating-point remainder value function

```c
#include <math.h>

double fmod(double x, double y);
float fmodf(float x, float y);
long double fmodl(long double x, long double y);
```

Compile for ``math.h``: ``gcc test.c -lm``

# double
## Binary conversion
IEEE 754 defines the double to binary conversion as:
```
| Sign bit (1 bit) | Exponent (11 bits) | Significand (52 bits) |
```
* Sign bit: 0 means positive number
* Significand: This part represents the fractional component of the number. The leading bit is typically implied to be 1, except for special cases.

Base on this definition, this uint8_t array ``{0, 0, 0, 0, 0, 144, 69, 64}`` results in number ``43.125``. Luckily, G++ has [reinterpret_cast](https://github.com/TranPhucVinh/Cplusplus/blob/master/Introduction/Data%20type/Explicit%20type%20conversion.md#reinterpret_cast) function which helps converting the uint8_t array to double number easily.

## long float
**double** can also be declared as **long float**.

```
float -> %f

double -> %lf
```

## Comparing float and double

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
