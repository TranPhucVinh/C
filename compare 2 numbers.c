#include <stdio.h>

// compare 2 numbers and print out the square of number from 1 to n

main() {

	int n;, 

	printf(" enter your number: ");

	scanf("%d", &n); // if you type scanf("&d ", &n) => C compile require you to press any keys after entering the number n value
	
	for (int i =0; i <= n; i++)
		{ int a = i*i;
printf("%d \n", a );
		}
}