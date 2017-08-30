// we create function for factorial, fracture ( 1/1 +1/2 +1/3+.. +1/x)

#include <stdio.h>

int factorial (int n)

{
 int m=1;
	for (int i = 1; i<=n; i++)
	{  
		m=m*i;
	}
	return m;
}

double fracture (int n)

{ double m = 0.0;

	for (double i = 1.0; i<=n; i++)
	{
 m = m +(1/i);
	}
	return m;
}

main() 

{
int n;
	scanf("%d",&n);
printf("%d \n", factorial(n) );
	printf("%lf \n", fracture(n) );
}