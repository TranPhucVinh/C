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

Enter a char, print out this char => learn how to use getchar(); putchar()

```c
#include <stdio.h>

main() {
	char a, b[1], c[1];
	a = getchar(); // get ASCII of the entered character

	putchar(a); // putchar is displaying the char on screen
	printf("\n");
	if (a == 'y') {
		printf("kill bugs");
	} else {
		printf("nothing here \n");
	} }
```
**NOTE:** ``"" vs ''``

``'' is for character, " " is for string``

Now we learn how to deal with entering the char inside if...else
```c
#include <stdio.h>

main() {
	scanf("%s", b);
	printf("%s \n", b);
	if ((strcmp(b, "t")) == 0) // must be "t", not 't'
	{
		scanf("%s", c);
		printf("%s \n", c);
		printf("The same character \n");
	} else {
		printf("Different \n");
	}
}
```
