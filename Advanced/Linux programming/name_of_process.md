Enter the id of the current process (if existed) then print out this process

```c
#include <stdio.h>
#include <stdlib.h> // For exit()

int main(){
	FILE *fptr;
	char processpath[100], c;
	int id;
	printf("Enter process id = ");
	scanf("%d", &id);
	sprintf(processpath, "/proc/%d/cmdline", id);
	fptr = fopen(processpath, "r");

	if (fptr == NULL){
		printf("No process id matching = %d \n", id);
		exit(0);
	}

	c = fgetc(fptr);
	while (c != EOF){
		printf("%c", c);
		c = fgetc(fptr);
	}

	fclose(fptr);
	return 0;
}
```

```c
int sprintf(char *str, const char *format, ...)
```

``sprintf()`` sending a formated string (``format``) to the string output (``str``)
