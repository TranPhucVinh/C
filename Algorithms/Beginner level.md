# Draw square with dots

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

# Find prime number

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

# Reverse number

Enter a number, print it in reverse order: 12345 => 54321; negative number, like -123, is invalid

```c
#include <stdio.h>
#include <stdlib.h>

int reverse_number(int old_number) {
    int tmp;
    long new_number = 0; // As there is "new_number*10 + tmp" in later step, so new_number must be long
    if (old_number < 0) {
        printf("Negative number can't be reversed\n");
        exit(0);
    }
    while(old_number != 0)
	{
		tmp = old_number%10;
		old_number = old_number/10;
		new_number = new_number*10 + tmp;
	}
    return new_number;
}

int main() {
    printf("%d\n", reverse_number(12345));
    return 0;
}
```
# Palindrome

Check if a string is palindrome: a word, phrase, or sequence that reads the same backward as forward, e.g., **madam** or **nurses run**.

```c
void isPalindrome(char* s) {
    int a = 0;
    for (int i=0; i < strlen(s); i++){
        if (s[i]==s[strlen(s)-1-i]){a++;}
        else {
            printf("String %s is not palindrome\n", s);    
            exit(0);        
        }
    }
    if ((a==(strlen(s)))){ 
        printf("String %s is palindrome\n", s);
    } 
}
```
