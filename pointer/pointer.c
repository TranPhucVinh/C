#include <stdio.h>

main() {

int a = 5;

printf("%p ", &a);

// print out the address of variable a: 0x7ffee13d1fa4 

int *p;

p = a;
printf("%d ", p); // result: 5

p = &a;
printf("%d \n", p); // result: 39367436 (address of variable - pointer p)

*p = a;
printf("%d ",p ); // result: 39367436 

}