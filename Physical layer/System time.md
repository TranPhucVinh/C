Library ``sys/time.h``

**Note**: The value of ``tv_usec`` is always less than one million.

**Example 1**: Get current time of day in Unix-alike system

```c
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main() {
  struct timeval tv;
  time_t t;
  struct tm *info;
  char buffer[64];
 
  gettimeofday(&tv, NULL);
  t = tv.tv_sec;

  info = localtime(&t);
  printf("%s",asctime (info));
  strftime (buffer, sizeof buffer, "Today is %A, %B %d.\n", info);
  printf("%s",buffer);
  strftime (buffer, sizeof buffer, "The time is %I:%M %p.\n", info);
  printf("%s",buffer);

  return 0;
}
```
**Example 2**: Delay for a number of seconds

```c
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void delaySeconds(long seconds);

int main(){
    while (1){
		printf("Hello, World !\n");
		delaySeconds(5);
	}

    return 0;
}

void delaySeconds(long seconds){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long totalSecond = 0;//ESP-IDF requires initialize for this variable
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}
```

## Other libraries

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

An inefficient way to delay 1 second as its delay time varies in vavrious processing core:

```c
void delayOneSecond();  

int main(){ 
    while (1){
      printf("Hello, World \n");
      delayOneSecond();
	}
} 

void delayOneSecond(){
  int c, d;
  for (c = 1; c <= 32767; c++){
    for (d = 1; d <= 32767; d++){};
  }
}
```
