Using formated output in ``printf()``:

```c
const char* string_output_format = "Displayed string: %s\n";
char displayedString[] = "Hello, World !";
printf(string_output_format, displayedString);       
```

### Print out an entered string and an entered character

```c
#include <stdio.h> 

int main() 
{ 
   char displayedString[80], enteredChar;
      
   scanf("%s", displayedString); 
      
   enteredChar = getchar(); 
      
   printf("%s\n", displayedString);       
   printf("%c\n", enteredChar); 
      
   return 0; 
} 
```

**Input**

```
Hello
a
```

**Output** ``Hello``

**Explain**: On pressing ``Enter`` (carriage return) on output screen after the first input, as the buffer of previous variable was the space for new container (as we didn't clear it) , the program skips the following input of container. This problem especially happens with ``scanf()`` function.

**Problem solve**: Add ``while ((getchar()) != ‘\n’)``

This will reads the buffer characters till the end and discards them(including newline) and using it after the ``scanf()`` statement clears the input buffer and allows the input in the desired container.

```c
scanf("%s", displayedString); 
while ((getchar()) != '\n');
enteredChar = getchar(); 
```

**Other example**: Enter 2 strings with ``scanf()`` and ``fgets()``

```c
char displayedString1[80], displayedString2[80];

scanf("%s", displayedString1);
while ((getchar()) != '\n'); //Must have this line
fgets(displayedString2, 80, stdin);    
   
printf("%s\n", displayedString1); 
printf("%s", displayedString2); 
```

### The problem doesn't happen with fgets()

If putting ``fgets()`` before ``scanf()``, ``getchar()``,... nothing will happen.

```c
char displayedString[80], enteredChar;
fgets(displayedString, 80, stdin); 

enteredChar = getchar(); 
printf("%s", displayedString); 
printf("%c \n", enteredChar);
```

**Input**

```
Hello, World !
1
```
**Output**
```
display string
1 
```

### Compare the entered string

Compare the entered string:
* If enter ``1``, print ``Enter 1``
* If enter ``2``, print ``Enter 2``
* If enter wrong string, print ``Enter wrong number``, then back to loop to ask user to re-enter.

**Notice**: Without ``while ((getchar()) != '\n')``, the program will go back to the lable ``PRINT_LABEL`` multiple times.

```c
#include <stdio.h>
#define BUFFSIZE 1

char buffer[BUFFSIZE];

int main(){
	PRINT_LABEL:	

	    fgets(buffer, 2, stdin);
        while ((getchar()) != '\n');

		if (buffer[0] == '1') puts("Enter 1");
		else if (buffer[0] == '2') puts("Enter 2");
		else {
			puts("Enter wrong number");
			goto PRINT_LABEL;
		}	

	return 0;
}
```
