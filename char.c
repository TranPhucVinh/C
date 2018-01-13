#include < stdio.h >

  main() {

    // enter a char, print out this char => learn how to use getchar(); putchar()

    char a, b[1], c[1];
    a = getchar(); // get ASCII of the entered character

    putchar(a); // putchar is displaying the char on screen
    printf("\n");

    //we will find out if the number entered is lowercase or uppercase
    if (a == 'y') {
      printf("kill bugs");
    } else {
      printf("nothing here \n");
    }
    // from here, you need to distinguished the different between "" and ''. '' is for character, " " is for string

    // now we learn how to deal with entering the char inside if...else

    scanf("%s", b);
    printf("%s \n", b);
    if ((strcmp(b, "t")) == 0) // must be "t", not 't'
    {
      scanf("%s", c);
      printf("%s \n", c);
      printf("roc \n");
    } else {
      printf("fuck the system \n");
    }

  }

//result :
/*
g
g
nothing here 
t
t 
g
g 
roc 

*/
/*
From here, we know that getchar can be executed only one time ina program */