# Find a first part and second part of a string splitted by a substring 

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPLIT_STR	"or"

char displayed_string[] = "Hello, World !";
char *second_part = NULL;
char *first_part = NULL;

int main(int argc, char *argv[]){
    second_part = strstr(displayed_string, SPLIT_STR);
	first_part = (char*) malloc((second_part - displayed_string) * sizeof(char));

    //Copy (second_part - displayed_string) character from displayed_string to first_part
    strncpy(first_part, displayed_string, second_part - displayed_string);

	printf("First part: %s\n", first_part);
	if (second_part != NULL) printf("Second part: %s\n", second_part);//orld !
	else printf("Second part: NULL\n");
	free(first_part);
	//As second_part is returned from strstr(), must not run it with free(second_part)
}
```
**Result**
```
First part: Hello, W
Second part: orld !
```

# Split a string by substring

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *remove_substring(char *string, char *sub) {
    char *new_string = (char*) malloc(strlen(string) * sizeof(char));
    char *second_part = (char*) malloc((strlen(string) - strlen(sub)) * sizeof(char));

    char *match;
    int len = strlen(sub);

    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(second_part, match+len);
    }

    strcat(new_string, string);//string now has the value of the first part of char *string
    strcat(new_string, second_part);
    free(second_part);

    return new_string;
}
 
int main(int argc, const char *argv[]) {
    char test[] = "Hello, World!";
    char *new_string = remove_substring(test, "ll");
    printf("%s\n", new_string);
    free(new_string);
    return 0;
}
```

**Result**: ``Heo, World!``

# Replace substring inside a string

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char displayed_string[] = "String 1 underscore String 2";

char *replace_string_by_substring(char *original_string, char *substring, char *replace);

int main(){
    char *new_string = replace_string_by_substring(displayed_string, "underscore", "_");
    printf("%s\n", new_string);//String 1 _ String 2
    free(new_string);
}

char *replace_string_by_substring(char *orginal_string, char *substring, char *replace){
    char* match = strstr(orginal_string, substring);
    if(match)
    {
        int new_size = strlen(orginal_string) - strlen(substring) + strlen(replace) + 1;
        char* new_string = (char*) malloc(new_size);
        bzero(new_string, new_size);
        *match = '\0';
        strcat(new_string, orginal_string);
        strcat(new_string, replace);
        strcat(new_string, match + strlen(substring));
        return new_string;
    }
    else return NULL;
}
```
# Split string with \x0a

## Split an internal variable string by ``\x0a``

```c
#define SPLIT_STR	"\x0a"
// #define SPLIT_STR[] "\\x0a"//this cause Segmentation fault

char displayed_string[] = "line1\x0aline2";
char *second_part = NULL;
char *first_part;

int main(int argc, char *argv[]){
    second_part = strstr(displayed_string, SPLIT_STR);
	first_part = (char*) malloc((second_part - displayed_string) * sizeof(char));
	
    strncpy(first_part, displayed_string, second_part - displayed_string);

	printf("%s\n", displayed_string);

	printf("First part: %s\n", first_part);
	if (second_part != NULL) printf("Second part: %s\n", second_part);//orld !
	else printf("Second part: NULL\n");

	free(first_part);
}
```
**Result**

```
line1
line2
First part: line1
Second part: 
line2
```

**Issue with escape character \\**: As ``\`` is escape character, adding one more ``\`` to the macro to make use of this character will cause the Segmentation fault issue

```c
#define SPLIT_STR "\\x0a"//this cause Segmentation fault
```

## Split a string read from file by ``\x0a``

File ``message`` includes:

```
line1\x0aline2
```

```c
// #define SPLIT_STR	"\x0a"//this cause Segmentation fault
#define SPLIT_STR 	"\\x0a"

char displayed_string[50];
char *second_part = NULL;
char *first_part;

int fd;

int main(int argc, char *argv[]){
	fd = open("message", O_RDONLY);
	read(fd, displayed_string, sizeof(displayed_string));
	printf("%s\n", displayed_string);

    second_part = strstr(displayed_string, SPLIT_STR);
	first_part = (char*) malloc((second_part - displayed_string) * sizeof(char));
	
    //Copy (second_part - displayed_string) character from displayed_string to first_part
    strncpy(first_part, displayed_string, second_part - displayed_string);

	printf("First part: %s\n", first_part);//Hello, W
	if (second_part != NULL) printf("Second part: %s\n", second_part);//orld !
	else printf("Second part: NULL\n");

	free(first_part);
}
```
**Result**
```
line1\x0aline2
First part: line1
Second part: \x0aline2
```

**Issue when not using escape character \\\\**: When not using escape character like this ``#define SPLIT_STR	"\x0a"``, the Segmentation fault issue will happen. This issue is contrasted [splitting an internal variable string by \x0a]().

```c
#define SPLIT_STR	"\x0a"//this cause Segmentation fault
```

**Split a string read from file by \x0a** method is applied to [kmess program](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/System%20call/kmess), which is used to display the kernel log in realtime.