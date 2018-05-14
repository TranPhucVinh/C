**pointer**

pointer: variable that stores address of other variable

*p: declare a pointer

*p : value at address

`````c
int a;
int *p; //pointer to integer
char c;
char *p0; //pointer to character
double d;
double *p1; // pointer to double
`````

%p: to print out the address

&: get the address of the variable


`````c
printf("%p", &a);
`````
`````c
p = &a //p is the address of a
`````

**A basic declaration with pointer**

`````c
int a;
int *p;

a = 5;
p = &a; // p is address of variable a
`````
### C

```c++
#include <stdio.h>
int val =5;
int *p = &val;

void main()
{
printf ("Value: %d", *p);	
}
```

### C++

```c++
#include <iostream>

using namespace std;
int val =5;
int *p = &val;
main(){
	cout << "value: " << *p;
}
```

```c
#include <stdio.h>

void add (int number);

main () {
 int number = 6;
 add(number);
 printf("%d", number);
}

void add(int number){
	number = number + 1;
}
```
**Result** 6 (expect 7)

```c
#include <stdio.h>

int add (int number);

main () {
 int number = 6;
 add(number);
 printf("%d", number);
}

int add(int number){
	number = number + 1;
	return number;
}
```
**Result** 6 (expect 7)

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
