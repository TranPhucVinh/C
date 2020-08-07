## exit()

Exit the current process and return value **status** for the further process.

```c
void exit(int status) 
```

```c
#include <stdio.h>
#include <stdlib.h> // For exit()

int main(){
	for(int i=0;i<10;i++){
		printf("number: %d \n", i);
		exit(0);
	}
}
```

**Result** ``number: 0 ``


### Get process name

Enter the id of the current process (if existed) then print out this process

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