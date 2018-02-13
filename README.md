# C

## Compile

To compile code C in sublime text, notepad, gedit,...

follow this link:
[How to Compile and Execute C/C++ Program On Ubuntu using Terminal Gedit, Sublime Text Editor](https://www.youtube.com/watch?v=QU8arxnpfhA)

to run the code: cd to current c workspace:

then type: ./<name of project>
 
Format code: [Sublime Text 2 & 3 AStyle Formatter Plugin](https://packagecontrol.io/packages/SublimeAStyleFormatter)

Ctrl +alt +f
  
## Library

**stdio.h:** standard io

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
### float and double

**double** can also be declared as **long float**.

float -> %f

double -> %lf

### static

**static:** local variable but the value remain unchanged in a function

## BEGINNER

#### scanf

`````c
scanf("%d ", &a);
`````
You have to type value a; then type one more to finish command although the value of **a** is still printed out correctly. To print out the value of **a** just after typing it, delete the space after %d

`````c
scanf("%d", &a);
`````

**Example**

`````c
#include <stdio.h>

void main() {
	int a;
	scanf("%d ", &a);
	printf("%d",a);
}
`````

#### printf

`````c
printf("%d ", a) // int
printf("%s ", a) // string
`````

### COMPARE

| C | JavaScript|
| ------- |:------:|
|int a = 8; | var a = 8;|
| printf("%d ",a)    | console.log(a)    |

**" " and ' '**

* ' ' is for character

* " " is for string

## CHEATSHEAT

