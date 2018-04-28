Drawing 

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

	int n,m;

	printf("enter m " );
	scanf("%d",&m);
	printf("enter n");
	scanf("%d",&n);
	for (int i=1; i<=n ; i++)
	{
		if ((i==1) || (i==n) )
			{ 
for (int j=1; j<=m; j++)
{
printf("*");
}
printf("\n");
			}
			else {
				for (int j =1; j<=m; j++)
				{
					if ( (j==1 )|| (j==m))
					{
  					printf("*");
					}
					else{
						printf(" ");
					}
				}
				printf("\n");
			}
	}
} 
```
