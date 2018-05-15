## Data Type

### char

can store character or integer value

`````c
// character
char c;
c = 'a';
printf("Character %c ", c);
`````

`````c
// integer
char c;
c = 8;
printf("Integer %d ", c);
`````

**Notes**

``char c ='ab'`` => Warning "character constant too long for its type"
=> WRONG

So, char in C go only with one word.
#### gets()

**gets()** is used to enter a string

`````c
#include <stdio.h>

int main () {
   char str[50];

   printf("Enter a string : ");
   gets(str);

   printf("You entered: %s", str);

   return(0);
}
`````
**Result**

```
Enter a string : tutorialspoint.com

You entered: tutorialspoint.com
```
