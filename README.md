# c-programming

To compile code C in sublime text, notepad, gedit,...

follow this link:
[How to Compile and Execute C/C++ Program On Ubuntu using Terminal Gedit, Sublime Text Editor](https://www.youtube.com/watch?v=QU8arxnpfhA)

to run the code: cd to current c workspace:

then type: ./<name of project>
 
Format code: [Sublime Text 2 & 3 AStyle Formatter Plugin](https://packagecontrol.io/packages/SublimeAStyleFormatter)

Ctrl +alt +f
  
## Acronym

**stdio.h:** standard io


**static**

static: local variable but the value remain unchanged in a function

### COMPARE

int a = 8;

| C | JavaScript|
| ------- |:------:|
| printf("%d ",&a)    | console.log(a)    |

**" " and ' '**

* ' ' is for character

* " " is for string

## CHEATSHEAT

**printf**

`````c
printf("%d ", &a) // int
printf("%s ", &a) // string
`````

**pointer**

pointer: variable that stores address of other variable

*p: declare a pointer

*p : value at address

`````c
int a;
int *p; //pointer to integer
char c;
char *p0; //pointer to character
double d;
double *p1; // pointer to double
`````

%p: to print out the address

&: get the address of the variable


`````c
printf("%p", &a);
`````
`````c
p = &a //p is the address of a
`````

