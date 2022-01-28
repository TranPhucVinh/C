### Drawing 

```
   m 
********
*      *   n   
*      *     
********
```

```c
#include <stdio.h>
main() {
	int n, m;
	printf("enter m " );
	scanf("%d", &m);
	printf("enter n");
	scanf("%d", &n);
	for (int i = 1; i <= n ; i++)
	{
		if ((i == 1) || (i == n))
		{
			for (int j = 1; j <= m; j++)
			{
				printf("*");
			}
			printf("\n");
		}
		else {
			for (int j = 1; j <= m; j++)
			{
				if ((j == 1 ) || (j == m))
				{
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			printf("\n");
		}
	}
}
```

### Reverse number

Enter a number, print it in reverse order: 12345 => 54321

```c
#include <stdio.h>

main () {

	int a,b, number=0;

	printf("enter the value of a");
	scanf("%d",&a);

	while(a != 0)
	{
		b = a%10;
		a = a/10;
		number = number*10 + b;
	}
	printf("%d \n", number );
}
```
