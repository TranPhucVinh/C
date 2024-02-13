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

Find all prime numbers less than a given integer value

```c
#include <stdio.h>

#define NUMBER 100

int main () {
    for (int i = 1; i <= NUMBER; i++)
    {
		int total_divisor = 0;
        for (int j = 1; j <= i; j++)
        {
            if ((i % j) == 0) total_divisor++;
        }
        if (total_divisor == 2) printf("%d ", i);
    }
}
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

**Check if a linked list is palindrome**. E.g:
* 1->2->1 is palindrome
* 3->2->1 isn't palindrome
**Solution**: [Convert that linked list into an array](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/linked_list_to_array.c) then start traversing this array for palindrome validation.

**List all palindrome numbers from 1 to MAX_NUMBER**: [list_all_palindromes.c](list_all_palindromes.c) (using 2 methods brute force and self-generating them)
