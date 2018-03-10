Enter a char, print out this char => learn how to use getchar(); putchar()

#include <stdio.h>
```c
main() {
	char a, b[1], c[1];
	a = getchar(); // get ASCII of the entered character

	putchar(a); // putchar is displaying the char on screen
	printf("\n");
	if (a == 'y') {
		printf("kill bugs");
	} else {
		printf("nothing here \n");
	}
```
**NOTE:** ``"" vs ''``

``'' is for character, " " is for string``

Now we learn how to deal with entering the char inside if...else
```c
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
