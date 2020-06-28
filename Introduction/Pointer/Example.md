## Variable pointer in function 

```c
#include <stdio.h>

int add (int number);

main () {
 int number = 6;
 add(number);
 printf("%d \n", number);
 printf("the return value of the function is %d \n", add(number));
}

int add(int number){
	number = number + 1;
	return number;
}
```
**Result** 
```
6 
the return value of the function is 7 
```

What is sent to the function ``add(number)`` is the value of variable ``number`` ( = 6), not variable ``number``, the variable ``number`` in ``add()`` is just the clone of the genuine variale ``number``. So the value of number still remain unchanged.

### Problem solved

```c
#include <stdio.h>

int add (int *number);

main () {
 int number = 6;
 add(&number);
 printf("%d", number);
}

int add(int *number){
	*number = *number + 1;
	return *number;
}
```

**Result** 7

### Swap

```c
#include <stdio.h>
int a, b;
void swap(int *change1, int *change2);
main() {
	printf("Enter the 2 numbers: ");
	scanf ("%d", &a);
	scanf("%d", &b);
	printf("Values of a and b are %d %d \n", a, b);
	swap(&a, &b);
	printf("Values of a and b now are %d %d \n", a, b);
}

void swap(int *change1, int *change2){
	int temp;
	temp = *change1;
	*change1= *change2;
	*change2 = temp;
}
```
```
Enter the 2 numbers: 4
6
Values of a and b are 4 6 
Values of a and b now are 6 4 
```

### scanf()

``scanf()`` reads formatted input from stdin.

```c
int scanf(const char *format, ...)
```

**Explain**

```c
scanf("%d", &a);
```

To save the value of variable ``a``, we have to use ``&`` to get the address so that ``*&`` will return the value of variable a.