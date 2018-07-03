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

### Hanoi tower

```c
#include <stdio.h>

void moveDisk(int diskNumber, int startPos, int endPos, int midPos);

main(){
	int diskNumber;
	printf("Enter disk number: ");
	scanf("%d", &diskNumber);
	moveDisk(diskNumber, 1, 2, 3);
}

void moveDisk(int diskNumber,int startPos,int endPos,int midPos)
{
	if (diskNumber >1)
	{
			moveDisk(diskNumber-1, startPos, midPos, endPos);
			printf("move disk number %d from column %d to column %d \n", diskNumber, startPos, endPos);
			moveDisk(diskNumber-1, midPos, endPos, startPos);
	}
		else printf("move disk number 1 from column %d to column %d \n", startPos, endPos);
}
```
