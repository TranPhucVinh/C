## Printed out entered value

### printf()

```c
printf("%d ", a) // int
printf("%s ", a) // string
```

```c
char hw[] = "Hello, World!";
printf("%s ", hw);
```

### scanf()

#### Int, Long (double), Float

```c
scanf("%d", &a);
scanf("%lf", &b);
scanf("%f", &c);
```

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

### Char and String

#### Char

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

#### String

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

### gets()

**gets()** is used to read the entered a string, but this function is now **deprecated** and **removed** in C compiler

### puts()

**Prototype**

```c
int puts(const char *str)
```

```c
printf("hello \n");
puts("hello");
```

**Result**

```
hello
hello
```

### getchar(), putchar()

Enter a char, print out this char

```c
#include <stdio.h>

main() {
	char a, b[1], c[1];
	a = getchar(); // get ASCII of the entered character

	putchar(a); // putchar is displaying the char on screen
	printf("\n");
	if (a == 'y') {
		printf("kill bugs");
	} else {
		printf("nothing here \n");
	} }
```
**NOTE:** ``" "`` vs ``' '``

``''`` is for character, ``" "`` is for string

Now we learn how to deal with entering the ``char`` inside ``if...else``

```c
#include <stdio.h>

main() {
	scanf("%s", b);
	printf("%s \n", b);
	if ((strcmp(b, "t")) == 0) // must be "t", not 't'
	{
		scanf("%s", c);
		printf("%s \n", c);
		printf("The same character \n");
	} else {
		printf("Different \n");
	}
}
```

## continue vs break

### break

```c
for (i=0; i<10; i++){
		if(i==5) break;
		printf("i value is %d \n", i);
	}
```

```
i value is 0 
i value is 1 
i value is 2 
i value is 3 
i value is 4 
```

### continue

```c
for (i=0; i<10; i++){
		if(i==5) continue;
		printf("i value is %d \n", i);
	}
```

```
i value is 0 
i value is 1 
i value is 2 
i value is 3 
i value is 4 
i value is 6 
i value is 7 
i value is 8 
i value is 9 
```

**Another example**

```c
int i = 0, a=0, b=0;
    while(i<10){
        i++;
        printf("i: %d \n", i);
		if(i==5) continue;
		a++;
		b++;
		printf("a: %d \n", a);
		printf("b: %d \n", b);
		printf("\n");
	}
```	

```
i: 1 
a: 1 
b: 1 

...

i: 4 
a: 4 
b: 4 

i: 5  //a++, b++ are bypass

i: 6 
a: 5 
b: 5 
...
i: 10 
a: 9 
b: 9 
```