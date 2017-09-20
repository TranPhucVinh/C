#include <stdio.h>

main() {

	// enter a char, print out this char => learn how to use getchar(); putchar()

char a;
a = getchar(); // get ASCII of the entered character

putchar(a); // putchar is displaying the char on screen
printf("\n");

//we will find out if the number entered is lowercase or uppercase
if (a =='y')
{
	printf("kill bugs" );
}
else
{
printf("nothing" );
}
 // from here, you need to distinguished the differ between "" and ''. '' is for character, " " is for string
}