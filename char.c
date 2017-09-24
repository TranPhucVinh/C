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
	printf("nothing here \n" );
}
 // from here, you need to distinguished the different between "" and ''. '' is for character, " " is for string

// now we learn how to deal with entering the char inside if...else
char b,c;
b = getchar();
if ( b == 't'  )
{
c =getchar();
putchar(c);
}
else {
	printf("fuck the system \n" );
}

}
