**Example 1**: Remove the first character from a string

```c
#include <stdio.h>
#include <string.h>

char telegramReturn[] = ",\"chat\":{\"id\":-1001452272470,\"title\":\"TMA lab 6 SW\",\"type\":\"supergroup\"";

void firstCharRemove(char stringChar[500]);

int main(){
	firstCharRemove(telegramReturn);
	printf("%s", telegramReturn);
}

void firstCharRemove(char stringChar[500]){
    //remove character ","
	if (stringChar[0] == ',') memmove(stringChar, stringChar+1, strlen(stringChar));
}
```

**Example 2**: Remove a specific index character from executed argument

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char displayedString[] = "Hello, World !";

void splitStringByIndex(int index, char* string);

char *dummyString;
int enteredIndex; 

int main(int argc, char *argv[]) {
    if (argc == 2){
		enteredIndex = strtol(argv[1], &dummyString, 10);
		if (!strcmp(dummyString, "")){
			if (enteredIndex < 0) {
				printf("Negative index value is invalid\n");
				return 0;
			}
			if (enteredIndex > strlen(displayedString)){
				printf("Index is bigger than string size\n");
				return 0;
			}

			printf("String before delete: %s\n", displayedString);
			splitStringByIndex(enteredIndex, displayedString);
			printf("String after delete: %s\n", displayedString);
        } else {
			printf("You have entered invalid index value");
		}
    } else if (argc > 2) puts("Just only one argument is excepted");
    else puts("You haven't entered anything");   
    return(0);
}

void splitStringByIndex(int index, char* string){
	int i = index;

	while(i <= strlen(string)){
		string[i] = string[i+1];
		i++;
	}
}
```
