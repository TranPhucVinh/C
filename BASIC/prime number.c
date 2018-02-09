#include <stdio.h>

main () {

	int n, count = 0;
	printf(" enter the limit value " );
	scanf("%d", &n);

	if (n <= 0)
	{
		printf("shitty");
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

//result:
// on terminal
// enter the limit value 29
// 2 3 5 7 11 13 17 19 23 29
