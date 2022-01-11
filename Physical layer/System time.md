## __DATE__ and __TIME__

```c
#include <stdio.h> 

int main(){ 
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
}
```

## sys/time

Library ``sys/time.h`` defines:

```c
struct timeval
{
  __time_t tv_sec;		/* Seconds.  */
  __suseconds_t tv_usec;	/* Microseconds.  */
};
```

```c
gettimeofday(&tv, NULL);
```

**Note**: The value of ``tv_usec`` is always less than one million.

Library ``time.h`` defines

* ``time()``
* ``localtime()``
* ``asctime()``
* ``strftime()``
* ``clock()``: returns the number of clock ticks elapsed since the start of the program

```c
#define CLOCKS_PER_SEC  ((clock_t) 1000000)
```

### Example 1

Get current time with ``time()``

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t currentTime;
    time(&currentTime); //Get current time and save to currentTime
    printf("%s", ctime(&currentTime));//Wed Aug 18 01:00:26 2021
    return(0);
}
```
``currentTime`` can also be defined as:

```c
time_t currentTime = time(NULL);
```

Get day, month and year with ``localtime()``

```c
time_t currentTime;
time(&currentTime); //Get current time and save to currentTime
struct tm *time_value = localtime(&currentTime);
printf("Day: %d, month: %d, year: %d", time_value->tm_mday, time_value->tm_mon, time_value->tm_year);
```
Get total second with ``clock()``:
```c
delaySeconds(5); //Function delaySeconds() defines in Example 3
int ticks = clock();
printf("total second: %f", (float) ticks/CLOCKS_PER_SEC);//total second: 4.766941
```

Get current time of day in Unix-alike system

```c
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
  struct timeval tv;
  time_t t;
  struct tm *info;
  char buffer[64];
 
  gettimeofday(&tv, NULL);
  t = tv.tv_sec;

  info = localtime(&t);
  printf("%s", asctime(info));
  strftime (buffer, sizeof buffer, "Today is %A, %B %d.\n", info);
  printf("%s", buffer);
  strftime (buffer, sizeof buffer, "The time is %I:%M %p.\n", info);
  printf("%s",buffer);

  return 0;
}
```

Convert epoch time to human readable time:

```c
time_t currentTime;
currentTime = 1641196080;//total second since Epoch
printf("%s", ctime(&currentTime));//Mon Jan  3 14:48:00 2022
```    

### Example 2

Delay for a number of seconds

```c
#include <stdio.h>
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
	long totalSecond = 0;
	long previousTime = tv.tv_sec;
	while (totalSecond - previousTime < seconds){
		gettimeofday(&tv, NULL);
		totalSecond = tv.tv_sec;
	}
}
```

### Example 3

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
