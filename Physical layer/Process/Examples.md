### Example 1

Enter the id of a process (if existed) then print out this process name.

```c
#include <stdio.h>
#include <stdlib.h>

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