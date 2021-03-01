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

* argv[1]: Index to remove character
* argv[2]: String to process

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void splitStringByIndex(int index, char* string);

char *dummyString, *enteredString;
int enteredIndex; 

int main(int argc, char *argv[]) {
    if (argc == 3){
		enteredString = argv[2];
		enteredIndex = strtol(argv[1], &dummyString, 10);
		if (!strcmp(dummyString, "")){
			if (enteredIndex < 0) {
				printf("Negative index value is invalid\n");
				return 0;
			}
			if (enteredIndex > strlen(enteredString)){
				printf("Index is bigger than string size\n");
				return 0;
			}

			printf("String before delete: %s\n", enteredString);
			splitStringByIndex(enteredIndex, enteredString);
			printf("String after delete: %s\n", enteredString);
        } else {
			printf("You have entered invalid index value");
		}
    } else if (argc > 3) puts("Just only one argument is excepted");
    else puts("You haven't entered enough parameter");   
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
