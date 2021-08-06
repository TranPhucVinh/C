### Example 1

Print out ``Hello world`` if signal ``12`` (``SIGUSR2``) is sent to PID of this process

```c
//Start an infinite loop and handle with signal
#include <stdio.h> 
#include <stdlib.h>
#include <signal.h> 
  
void signal_handler(int signalNumber){
	if (signalNumber == 12){
		//printf("You have entered signal number 12"); 
		//printf might not work properly due to several OS problem, so use puts() instead to print of pure string;

		puts("Hello world");
	}
}

int main(){ 
	signal(12, signal_handler);
	while(1);
} 
```

In other terminal

Run ``ps aux|grep a.out``: Find PID of ``a.out``. E.g PID of ``a.out`` is 1234

Run ``kill -12 1234``