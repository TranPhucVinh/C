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
