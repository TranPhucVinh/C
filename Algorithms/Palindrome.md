# Reverse number

An approach for palindrome is to reverse a number. E.g 12345 => 54321; negative number, like -123, is invalid

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
# Check if a string is palindrome

Palindrome a word, phrase, or sequence that reads the same backward as forward, e.g., **madam** or **nurses run**.

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
To reduce traversing time, just traverse to the middle of the string, i.e **strlen(s)/2**:
```c
void isPalindrome(char* s) {
    int a = 0;

    if (strlen(s) == 3) {
        if (s[0] == s[2]) printf("String %s is palindrome\n", s);
        else printf("String %s is not palindrome\n", s);
        return;
    }

    for (int i=0; i < strlen(s)/2; i++){
        if (s[i]==s[strlen(s)-1-i]) a++;
        else {
            printf("String %s is not palindrome\n", s);    
            exit(0);        
        }
    }

    if (a == strlen(s)/2) printf("String %s is palindrome\n", s);
}
```
# Check if a phrase is a palindrome
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

E.g: "A man, a plan, a canal: Panama" is a palindrome phrase as amanaplanacanalpanama is a palindrome

Source code: [palindrome_phrase_validity.cpp](src/palindrome_phrase_validity.cpp)
# Given a string s, return true if the s can be palindrome after deleting at most one character from it

* s = "abca" -> true as you could delete the character 'c'.
* s = "abc" -> false.
* s = "cbbcc" -> true you could delete the character 'c' at index 3, s= "cbbc"
# Check if a linked list is palindrome
E.g:
* 1->2->1 is palindrome
* 3->2->1 isn't palindrome
**Solution**: [Convert that linked list into an array](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/linked_list_to_array.c) then start traversing this array for palindrome validation.

# List all palindrome from 1 to MAX_NUMBER, generate all palindrome with a fixed length
**Source code**: [list_all_palindromes.c](list_all_palindromes.c)

**Notes**: [Function listPalindrome()](src/list_all_palindromes.cpp#L30C6-L30C20) is a brute force approach to list all palindrome, while we can use the self-generating method as a better solution.
# Find palindrome with fixed length

Given an integer array **queries** and a positive integer **intLength**, return an array **_Palindromes** where **_Palindromes[i]** is either the **queries[i]th** smallest positive palindrome of length **intLength** or **-1** if no such palindrome exists.

**Test case 1**:

* Input: queries = [1,2,3,4,5,90], intLength = 3
* Output: [101,111,121,131,141,999]
* Explanation:
The first few palindromes of length 3 are:
```
101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, ...
```
The 90th palindrome of length 3 is 999.

**Test case 2**:

* Input: queries = [2,4,6], intLength = 4
* Output: [1111,1331,1551]
* Explanation:

The first six palindromes of length 4 are:

1001, 1111, 1221, 1331, 1441, and 1551.

## Solution

A high time-complexity approach is to generate all panlindrom with length **intLength** then starts finding the **queries[i]th** inside that array. This approach takes many time to execute when intLength >= 13.

The **best approach** is to generate only the smallest positive palindrome based on **queries[i]th**.

## Analysis for the best approach

The even number palindrome with length **intLength**, e.g 1221, 3223,.. (``intLength=4``) can be generate from the number of **intLength/2** length. E.g 12, 34,... will generate 1221, 3443,...

The odd number palindromes with length **intLength**, e.g 12321, 32123,.. (``intLength=5``) can be generate from the number of **intLength/2 + 1** length. E.g 123, 321,... will generate 12321, 12321,... (as we remove the "number at middle index")

Take an example with ``intLength = 4``, by this mechanism (for even number palindrome), we can generate a list of ascending palindrome if we generate from the ascending numbers of ``intLength/2 = 2`` length.

```
10 -> 1001 # 1st smallest
11 -> 1111 # 2nd smallest
12 -> 1221 # 3rd smallest
..
98 -> 9889 # 98st smallest
99 -> 9999 # 99st smallest
```

For the list above, with queries[i] = 3, generate number ``1221`` from ``12`` for the 3rd smallest.

By this approach, we will save time as we only generate the **queries[i]th smallest number required**, not generating all palindromes.

Similar implementation for odd number palindromes.

**Source code**: [palindrome_find_palindrome_with_fixed_length.cpp](src/palindrome_find_palindrome_with_fixed_length.cpp)
# Prime palindrome

Given an integer **n**, return the smallest prime palindrome >= **n**.

Example 1:
* Input: n = 6
* Output: 7

Example 2:
* Input: n = 8
* Output: 11

Example 3:
* Input: n = 13
* Output: 101

## Bruce force approach

A note for brute approach is that except 11, all prime palindrome has odd length (as all odd length palindrome are divisible by 11.

So to limit the calculation process in brute force approach, with 10000000 <= n < 1000000000 (8 char), start find from  n = 100000000

**Source code**: [palindrome_prime_palindrome_brute_force.cpp](https://github.com/TranPhucVinh/C/blob/master/Algorithms/src/palindrome_prime_palindrome_brute_force.cpp)

## Analysis for the best approach

Except 11, all prime palindrome has odd length (as all odd length palindrome are divisible by 11.

**Prove**: For any palindrome with even length: ``abcddcba = (a * 10000001 + b * 100001 * 10 + c * 1001 * 100 + d * 11 * 1000) % 11 = 0``

The approach is to generate all palindrome from the size of the required number **n**, then check if that newly generated palindrome is prime. If not, keep generating.

**Source code**: [palindrome_prime_palindrome_generate_prime_palindrome.cpp](https://github.com/TranPhucVinh/C/blob/master/Algorithms/src/palindrome_prime_palindrome_generate_prime_palindrome.cpp)
