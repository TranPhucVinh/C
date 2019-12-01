## printf()

### Print out string

```c
#include <stdio.h>

int main () {
    printf("%s \n", "Hello, World!");
    printf("Hello, World! with no %s");
}
```
**Result**

```
Hello, World!
Hello, World! with no 5c|
```

### Printed out entered value

```c
printf("%d ", a) // int
printf("%s ", a) // string
```

## scanf()

### Int, Long (double), Float

**Enter Int, Long (double), Float variable**

```c
scanf("%d", &a);
scanf("%lf", &b);
scanf("%f", &c);
```

**Enter 3 variables with 3 types of data then print out**

```c
int a;
double b;
float c;

scanf("%d", &a);
scanf("%lf", &b);
scanf("%f", &c);

printf("value %d %lf %f", a, b, c);
```

**Result**

```
123 4555.999 9.08 (value you enter)
value 123 4555.999000 9.080000
```

### char

**Enter and print out char variable as integer number**

```c
char a;
scanf("%c", &a);
printf("value: %c", a);
```

**Result**

```
Enter 4 output 4
Enter a output a
Enter abc output a
```

**Convert value to Hex**

```c
int a = 19;
printf("a in hex 0x%x \n", a); //a in hex 0x13 
```

### Print out a string as char variable

Because the array with ``char a[10]`` is a pointer so it doesn't need the pointer get value ``&`` in scanf.

```c
char a[10]; //10 character of string
scanf("%s", a);
printf("value: %s", a);
```

### Whitespace problem

You have to type value a; then type one more to finish command although the value of **a** is still printed out correctly. To print out the value of **a** just after typing it, delete the space after ``%d``.

```c
scanf("%d", &a);
```

**Example**

```c
	int a;
	scanf("%d ", &a);
	printf("%d",a);
```