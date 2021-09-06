### Example 1

Print out a string if signal ``12`` (``SIGUSR2``) is sent to PID of this process

```c
#include <stdio.h>
#include <signal.h> 
  
#define SIGUSR2 12  

void signal_handler(int signalNumber){
	if (signalNumber == SIGUSR2){
		printf("You have entered signal number: %d\n", signalNumber); 
	}
}

int main(){ 
	signal(SIGUSR2, signal_handler);
	while(1);//Start an infinite loop and handle with signal
}
```

In other terminal

Run ``ps aux|grep a.out`` to find PID of ``a.out``. E.g PID of ``a.out`` is ``12976``

Run ``kill -12 1234``