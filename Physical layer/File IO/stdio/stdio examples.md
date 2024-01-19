# Print out an entered string and an entered character

```c
// THIS IS AN UNOPTIMIZED EXAMPLE INTENDED FOR EDUCATIONAL PURPOSE. MUST NOT DO THIS IN PRACTICAL IMPLEMENTATION
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

**Explain**: On pressing **Enter** (carriage return) on output screen after the first input, as the buffer of previous variable was the space for new container (as we didn't clear it), the program skips the following input of container. This problem especially happens with [scanf()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/File%20IO/stdio/stdin%20and%20stdout%20API.md#scanf) function.

**Problem solve**: Add ``while ((getchar()) != '\n')``

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

## The problem doesn't happen with fgets()

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

# Compare the entered string

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

# Print out all files (included folders) along with their types inside a folder with dirent.h

* ``opendir()``: Open directory
* ``readdir()``: Read directory

```c
#include <stdio.h>
#include <dirent.h>

int main(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir("."); //. for current folder
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s has type %d\n", dir->d_name, dir->d_type);
        }
        closedir(d);
    }
    return(0);
}
```
**Result**
```
FIFO has type 1
. has type 4
main.c has type 8
head.h has type 8
Makefile has type 8
.. has type 4
a.out has type 8
a.exe has type 8
head.c has type 8
```
``dirent.h`` file types:

```c
enum
{
    	DT_UNKNOWN = 0,
	# define DT_UNKNOWN	DT_UNKNOWN
	    DT_FIFO = 1,
	# define DT_FIFO	DT_FIFO
	    DT_CHR = 2,
	# define DT_CHR		DT_CHR
	    DT_DIR = 4,
	# define DT_DIR		DT_DIR
	    DT_BLK = 6,
	# define DT_BLK		DT_BLK
	    DT_REG = 8,
	# define DT_REG		DT_REG // Regular file
	    DT_LNK = 10,
	# define DT_LNK		DT_LNK
	    DT_SOCK = 12,
	# define DT_SOCK	DT_SOCK
	    DT_WHT = 14
	# define DT_WHT		DT_WHT
};
```
