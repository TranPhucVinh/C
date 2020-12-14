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

### Rectangle calculation

Calculate the perimeter and area of a rectangle base on the edge value entered when compiling the file

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int32_t rectangle_calculate(uint32_t a, uint32_t b, uint32_t *perimeter, uint32_t *area){
	if ((a == 0)||(b == 0)||(perimeter == NULL)||(area == NULL)){
		return 0;
	}
	else {
		*perimeter = (a+b)*2;
		*area = a*b;
		return 1;
	}
}

int main(int argc, char *argv[]){
	int a, b;
    char *tempString1, *tempString2;
    long ret;

    if (argc==3){
        a = strtol(argv[1], &tempString1, 10);
		b = strtol(argv[2], &tempString2, 10);
		printf("%d\n", a);
		printf("%d\n", b);
        if (strlen(tempString1)||strlen(tempString2)) {
            puts("You have entered the invalid index value");
            return 0;            
        }
    } else {
        puts("You haven't entered enough parameter to execute");  
        return 0;
    }

	int perimeter, area;
	if(!rectangle_calculate(a, b, &perimeter, &area)) {
		printf("Invalid edge size");
	} else {
		printf("Perimeter: %d, area: %d", perimeter, area);
	}
}
```