## printf()

### Print out string

```c
#include <stdio.h>

int main () {
    printf("%s \n", "Hello, World!"); //Hello, World!
}
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

scanf("%d", &a); //Enter: 123
scanf("%lf", &b); //Enter 4555.999
scanf("%f", &c); //Enter: 9.08

printf("value %d %lf %f", a, b, c); //value 123 4555.999000 9.080000

```

### char

**Enter and print out char variable as integer number**

```c
char a;
scanf("%c", &a);
printf("value: %c", a);
```

**Result**

    Enter 4 -> output 4
    Enter character a  -> output character a
    Enter abc -> output a

**Convert value to Hex**

```c
int a = 19;
printf("a in hex 0x%x \n", a); //a in hex 0x13 
```

### Whitespace problem

```c
int a;
scanf("%d ", &a);
printf("%d",a);
```

You have to type value a; then type one more to finish command although the value of ``a`` is still printed out correctly. To print out the value of ``a`` just after typing it, delete the space after ``%d``.

### Print out a string as char variable

Because the array with ``char a[10]`` is a pointer so it doesn't need the pointer get value ``&`` in scanf.

```c
char a[10]; //10 character of string
scanf("%s", a);
printf("value: %s", a);
```

If you type in value with whitespace, like ``Hello, World!``, this will just print out only ``Hello``.


### fgets()

To print out entered string included whitespace, using ``fgets()``: ``fgets(char *s, int n, FILE *stream)``

```c
char buf[15];
printf("Enter string: ");
fgets(buf, 15, stdin); 
printf("string is: %s\n", buf);
```

This will printout the entered string followed with a new line, to remove that new line:

```c
char buf[15];
printf("Enter string: ");
fgets(buf, 15, stdin); 
int len=strlen(buf); //where buff is your char array fgets is using
if(buf[len-1]=='\n')	buf[len-1]='\0';
printf("string is: %s\n", buf);
```

### Problem with scanf() before fgets()

As there is ``\n`` character goes after ``scanf()``, putting ``scanf()`` before ``fgets()`` will result in losing the ``fgets()`` command handler

**Problem solved**