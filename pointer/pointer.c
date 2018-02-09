#include <stdio.h>

main() {

	int a = 5;

	printf("%p \n", &a); // print out the address of variable a: 0x7ffee13d1fa4 => address change in RAM
	int *p;
	p = a;
	printf("%d \n", p); // result: 5
	p = &a;
	printf("%d \n", p); // result: 39367436 (address of variable a)
	printf("%d \n", *p ); // result: 5
}