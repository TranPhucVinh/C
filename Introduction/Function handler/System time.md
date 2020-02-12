### On Windows

Print out a string after every one second with library ``time.h``.

```c
#include <stdio.h> 
#include <time.h> 

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    clock_t start_time = clock(); // Storing start time 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 		; 
} 
  
// Driver code to test above function 
int main(){ 
    while (1){
		printf("Hello, World \n");
		delay(1);
	}
} 
```

### On Ubuntu/Linux

Print out a string after every one second with ``sleep()``.

```c
#include <stdio.h> 
#include <unistd.h>

int main(){ 
    while (1){
		printf("Hello, World \n");
		sleep(1);
	}
} 
```
