For ``getchar()``, use n+1 buffer to properly store n member.

Simulate the string entered problem with Keypad on MCU with getchar() in C.

### Example 1

Enter 4 number to set up the filled volume of a machine. Press ``#`` to finish entering

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