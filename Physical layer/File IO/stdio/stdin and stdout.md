## printf()

Sends formatted output to ``stdout``

```c
printf("%d ", a) // int
printf("%s ", a) // string
```

**Example**: ``printf("%s \n", "Hello, World!"); //Hello, World!``

**Return**: return the total print out character

```c
int returnPrintf = printf("Hello, World!\n");
printf("%d \n", returnPrintf); //14
```

## scanf()

Read formatted input from ``stdin``

```c
int scanf ( const char * format, ... );
```

**Return**: number of items of the argument list successfully filled. This will return ``1`` (valid data enter) and ``0`` for invalid data enter.


``scanf("%d", &a)``: Get the entered value from ``stdin`` and stored in the address of variable ``a``.

**Example**: Enter ``int``, ``long`` (double), ``float`` variable

```c
scanf("%d", &a);    //int
scanf("%lf", &b);   //long
scanf("%f", &c);    //float
scanf("%d%d", &a, &b); //More than 1 value can be passed to scanf
```

**Example**: Enter and print out ``char`` variable as ``integer`` number

```c
char a;
scanf("%c", &a);
printf("value: %c", a);
```

**Result**

    Enter 4 -> output 4
    Enter character a  -> output character a
    Enter abc -> output a

### Whitespace problem

```c
int a;
scanf("%d ", &a);
printf("%d", a);
```

You have to type value a; then type one more to finish command although the value of ``a`` is still printed out correctly. To print out the value of ``a`` just after typing it, delete the space after ``%d``.

### Print out a string as char variable

Because the array with ``char a[10]`` is a pointer so it doesn't need the pointer get value ``&`` in scanf.

```c
char a[10]; //10 character of string
scanf("%s", a);
printf("value: %s", a);
```

If you type in value with whitespace, like ``Hello, World!``, this will just print out only ``Hello,``.

Using ``scanf()`` is not highly recommended as it doesn't have buffer overflow protection, unless you know for certain that the input will always be of a specific format (and perhaps not even then).


A proper word entering can be solved with [fgets()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/FIle%20pointer%20API.md#fgets).

## %.*s

```c
void display_function(char *str, int str_len)
{
  printf("%.*s\n", str_len, str);
}

char *return_string(char *str, int str_len){
    char *returned_string = (char*) malloc(str_len + 1);
    sprintf(returned_string, "%.*s", str_len, str);
    return returned_string;
}

int main(){
    display_function("Hello, World !", 3);//Hel
    char *returned_string = return_string("Displayed string", 5);
    printf("%s\n", returned_string);//Displ
    free(returned_string);
}
```

## gets() and puts()

### gets()

**gets()** is used to read the entered a string, but this function is now **deprecated** and **removed** in C compiler. Just use ``scanf()`` instead.

### puts()

Writes a string to ``stdout`` followed with a new line

```c
int puts(const char *str)
```

```c
puts("hello"); //hello
```

## getchar(), putchar()

```c
int putchar(int char);
int getchar(void);
```

* ``getchar()``: gets a character (an unsigned char) from ``stdin``
* ``putchar()``: writes character (an unsigned char) ``char`` to ``stdout``

### getchar() examples

For ``getchar()``, use n+1 buffer to properly store n member.

Simulate the string entered problem with Keypad on MCU with getchar() in C.

**Example 1**: Enter 4 number to set up the filled volume of a machine. Press ``#`` to finish entering

E.g: If entering ``1234``, the software will display

``Filled value: 1234 ml``

```c
#include <stdio.h> 
#include <stdlib.h> //for atoi()
#include <string.h> 

int main() 
{ 
    char enteredChar;
    char volumeStringArray[5];//Use 5 index to properly store 4 value
    memset(volumeStringArray, 0, sizeof(volumeStringArray));
    
    int index = 0;
    char displayedString[16] = "Filled value ";
    while (enteredChar != '#'){
        enteredChar = getchar();
        //Only accept number from 0 to 9 to be entered
        if ((enteredChar >= 48) && (enteredChar <= 57)&&(index < 4)) {
            volumeStringArray[index] = enteredChar;
            index += 1;
        }    
    }
    int displayedNumber = atoi(volumeStringArray); //Display 0123 to 123
    sprintf(volumeStringArray, "%d", displayedNumber);
    strcat(displayedString, volumeStringArray);
    strcat(displayedString, " ml");
    printf("%s", displayedString);
}
```
