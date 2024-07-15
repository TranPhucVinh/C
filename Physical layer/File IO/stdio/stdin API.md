

# scanf()

Read formatted input from ``stdin``

```c
int scanf(const char * format,...);
```

**Return**: number of items of the argument list successfully filled. This will return ``1`` (valid data enter) and ``0`` for invalid data enter.


``scanf("%d", &a)``: Get the entered value from ``stdin`` and stored in the address of variable ``a``.

## Enter ``int``, ``long`` (double), ``float`` variable

```c
scanf("%d", &a);    //int
scanf("%lf", &b);   //long
scanf("%f", &c);    //float
scanf("%d%d", &a, &b); //More than 1 value can be passed to scanf
```

For float number, it must be ``scanf("%f", &c)``, not ``scanf("%.2f", &c)`` if you want to set a specific float number.

## Enter and print out ``char`` variable as ``integer`` number

```c
char a;
scanf("%c", &a);
printf("value: %c", a);
```

**Result**
```
Enter 4 -> output 4
Enter character a  -> output character a
Enter abc -> output a
```
## Must not have whitespace after format in scanf

```c
int a;
scanf("%d ", &a);
printf("%d", a);
```

You have to type value a; then type one more to finish command although the value of ``a`` is still printed out correctly. To print out the value of ``a`` just after typing it, delete the space after ``%d``.

## Whitespace issue with string

Because the array with ``char a[10]`` is a pointer so it doesn't need the pointer get value ``&`` in scanf.

```c
char str[10]; //string with 10 characters
scanf("%s", str);
printf("value: %s", str);
```

**Result** If you type in value with whitespace, like ``Hello, World!``, this will just print out only ``Hello,``.

Use [scanset character](#) ``[]`` to support entering the string included whitespace:
```c
char displayedString[80];
scanf("%[^\n]", displayedString);// Hello, World !
printf("%s\n", displayedString);// Hello, World !
```
Here,  ``^\n`` stands for taking input until a newline isn't encountered.

Using ``scanf()`` is not recommended as it doesn't have buffer overflow protection, unless you know for certain that the input will always be of a specific format (and perhaps not even then).

A proper word entering can be solved with [fgets()](File%20pointer%20API.md#fgets).
## scanset character

Scanset character ``%[]``, which is only supported in ``scanf()``, is used to can specify single character or range of characters to be accepted or ommited in the entered string.

This scanset implementation accept the capitalized entered string.
```c
char str[80];
memset(str, 0, 80);
printf("Enter a string: ");
scanf("%[A-Z]s", str);

printf("You entered: %s\n", str);  
```
**Result**
```
Enter a string: "Hello_World -> You entered: "H" (Capitalized "W" is ommited"
Enter a string: "HELLO_world" -> You entered: "HELLO"
Enter a string: "hEllo" -> You entered: "(null)" (1st character "h" isn't capitalized so the whole string is ommitted)
```

# gets() is deprecated

**gets()** is used to read the entered a string, but this function is now **deprecated** and **removed** in C compiler. Just use ``scanf()`` instead.

# getchar(), putchar()

```c
int putchar(int char);
int getchar(void);
```

* ``getchar()``: gets a character (an unsigned char) from ``stdin``
* ``putchar()``: writes character (an unsigned char) ``char`` to ``stdout``

For ``getchar()``, use n+1 buffer to properly store n member.

## Simulate the string entered process with [keypad](https://github.com/TranPhucVinh/AVR-Arduino-framework/tree/master/Sensors%20and%20Modules/GPIO%20modules/Keypad) on MCU with getchar() in C

This example with simulate the entering character process with Keypad connected to MCU, i.e entering every character by pressing the button on that keypad, by using ``getchar()`` function.

**Features**: Enter 4 number to set up the filled volume of a machine. Press ``#`` to finish entering

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
