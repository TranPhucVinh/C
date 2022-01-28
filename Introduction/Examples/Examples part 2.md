### Prime number

Find prime number with a limited of integer value

```c
#include <stdio.h>

main () {
	int n, count = 0;
	printf(" enter the limit value " );
	scanf("%d", &n);

	if (n <= 0)
	{
		printf("number must be greater than 0");
	}
	else
	{
		for (int i = 1; i <= n ; i++)
		{
			for (int j = 1; j <= i; j++)
			{
				if ((i % j) == 0)
				{
					count++;
				}
			}
			if (count == 2) {
				printf("%d ", i );
			}
			count = 0;
		}
	}
}
```

**Result**

```
enter the limit value 29
2 3 5 7 11 13 17 19 23 29
```
### Hanoi tower

```c
#include <stdio.h>

void moveDisk(int diskNumber, int startPos, int midPos, int endPos);

main(){
	int diskNumber;
	printf("Enter disk number: ");
	scanf("%d", &diskNumber);
	moveDisk(diskNumber, 1, 2, 3);
}

void moveDisk(int diskNumber, int startPos, int midPos, int endPos)
{
	if (diskNumber >1)
	{		// move n-1 upper disk from startPos to midPos
			moveDisk(diskNumber-1, startPos, endPos, midPos);
			//move the biggest disk from startPos to endPos
			printf("move disk number %d from column %d to column %d \n", diskNumber, startPos, endPos);
			// move n-1 upper disk from midPos to endPos
			moveDisk(diskNumber-1, midPos, startPos, endPos);
	}
		else printf("move disk number 1 from column %d to column %d \n", startPos, endPos);
}
```

### Select sort

```c
#include <stdio.h>

main(){
	int i, j, n, array[100], max, pos, temp;
	printf("Enter the number of members: ");
	scanf("%d", &n);
	printf("Enter the value of each member: ");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}
	for (i=0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	for (i=0; i<n-1; i++)
	{
		max = array[i];
		pos = i;
		for (j=i+1; j<n; j++)
		{
			if (max < array[j]){
				max = array[j];
				pos = j;
			}
		}	
			if (pos != i){
				temp = array[i];
				array[i] = max;
				array[pos] = temp;
			}
	}
	for (i=0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
}
```
