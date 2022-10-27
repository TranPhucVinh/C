# API

## __DATE__ and __TIME__

```c
#include <stdio.h> 

int main(){ 
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
}
```

## unistd.h

```c
unsigned int sleep(unsigned int seconds);//Sleep for a number of seconds
``` 

Print out a string every 1 second with ``sleep()``:

```c
#include <stdio.h>
#include <unistd.h>

#define DELAY_TIME 1

int main(int argc, char *argv[])  {
	while(1){
        printf("1 second delay\n");//Must have \n for proper print out
        sleep(DELAY_TIME);
    }
}
```

```c
typedef unsigned long useconds_t;
```

```c
int usleep(useconds_t usec);
```

``usleep``: suspend execution for microsecond intervals

Print out a string every 1 second with ``usleep()``:

```c
#include <stdio.h>
#include <unistd.h>

#define DELAY_TIME 1000000

int main(int argc, char *argv[])  {
	while(1){
        printf("Hello\n");//Must have \n for proper print out
        usleep(DELAY_TIME);
    }
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
struct rtc_time { 
    int tm_sec; /* Seconds (0-60) */
    int tm_min; /* Minutes (0-59) */
    int tm_hour; /* Hours (0-23) */
    int tm_mday; /* Day of the month (1-31) */
    int tm_mon; /* Month (0-11) */
    int tm_year; /* Year - 1900 */
    int tm_wday;     /* Day of the week (0-6, Sunday = 0)*/
    int tm_yday;     /* Day in the year (0-365, 1 Jan = 0)*/
    int tm_isdst;    /* Daylight saving time*/
};
```

```c
#define CLOCKS_PER_SEC  ((clock_t) 1000000)
```
