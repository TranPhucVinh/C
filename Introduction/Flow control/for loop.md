# Omit 1st expression

```c
int index = 0;
for(; index < 10; index++){
	printf("index: %d\n", index);
}
```
**Result**: Print out from ``0`` to ``9``.

# Omit 2nd expression
The 2nd expression now is ``true``

```c
for(int index = 0;;index++){
	printf("index: %d\n", index);// Infinite index count up by 1
}
```    
# Omit 3nd expression
```c
int index = 0;
for(int index = 0;index<10;){
	printf("index: %d\n", index);
}
```
**Result**: Print out ``0`` forever.

``for(;;)`` is equal to ``while(1)``.

Increase by a number in the 3rd expression
```c
for (int i = 0; i <= 10; i=i+2) {
        printf("%d ", i);
} // Result: 0 2 4 6 8 10
```
# Omit 1st and 3rd expressions
```c
int index = 0;
for(;index < 10;){
	printf("index: %d\n", index);// index from 0 to 9
	index++;
}
```
# Draw a rectangle with dots
```
column  
***
* * row
* *
***
```
```c
#include <stdio.h>
int main() {
	int column = 3;
    int row = 4;

	for (int i = 1; i <= row ; i++)
	{
		if ((i == 1) || (i == row))
		{
			for (int j = 1; j <= column; j++){
				printf("*");
			}
			printf("\n");
		}
		else {
			for (int j = 1; j <= column; j++)
			{
				if ((j == 1 ) || (j == column)) {
					printf("*");
				}
				else printf(" ");
			}
			printf("\n");
		}
	}
}
```
# Draw staircase
n = 6
```
     #
    ##
   ###
  ####
 #####
######
```
```c
void staircase(int n) {
    for (int i = 1; i <= n; i++){
        for (int j = n - i; j > 0; j--) printf(" ");
        for (int k = 1; k <= i; k++) printf("#");
        printf("\n");
    }
}
```
