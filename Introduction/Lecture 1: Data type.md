# Data type

![](datatype.png)

### COMPARE

| C | JavaScript|
| ------- |:------:|
|int a = 8; | var a = 8;|
| printf("%d ",a)    | console.log(a)    |

**" " and ' '**

* ' ' is for character

* " " is for string

### Example

```c
#include <stdio.h>
void main() {
	double x = 3.1;
	float y = 3.1;
	if (x == y){
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
}
```
**Result**
```
NO
```

### char

can store character or integer value

`````c
// character
char c;
c = 'a';
printf("Character %c ", c);
`````

`````c
// integer
char c;
c = 8;
printf("Integer %d ", c);
`````

**Notes**

``char c ='ab'`` => Warning "character constant too long for its type"
=> WRONG

So, char in C go only with one word.

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

```c
typedef unsigned int size_t;
```

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

### stdint.h

stdint.h - integer types

include 

```c
int8_t
int16_t
int32_t
uint8_t
uint16_t
uint32_t
```

### sprintf()

```c
/* sprintf example */
#include <stdio.h>

int main ()
{
  char buffer [50];
  int n, a=5, b=3;
  n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
  printf ("[%s] is a string %d chars long\n",buffer,n);
  return 0;
}
```

```
[5 plus 3 is 8] is a string 13 chars long
```
