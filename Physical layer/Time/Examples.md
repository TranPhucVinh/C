# Get current time with time()

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t currentTime;
    time(&currentTime);//Get current time as epoch time and save this to currentTime
    printf("%s", ctime(&currentTime));//Wed Aug 18 01:00:26 2021
    return(0);
}
```
``currentTime`` can also be defined as:

```c
time_t currentTime = time(NULL);
```

# Get day, month and year with localtime()

```c
time_t currentTime;
time(&currentTime); //Get current time and save to currentTime
struct tm *time_value = localtime(&currentTime);
printf("Day: %d, month: %d, year: %d", time_value->tm_mday, time_value->tm_mon, time_value->tm_year);
```
# Get total second with clock()
```c
delaySeconds(5); //Function delaySeconds() defines in Example 3
int ticks = clock();
printf("total second: %f", (float) ticks/CLOCKS_PER_SEC);//total second: 4.766941
```

# Get current time of day in Unix-alike system

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

**Convert epoch time to human readable time**

```c
time_t currentTime;
currentTime = 1641196080;//total second since Epoch
printf("%s", ctime(&currentTime));//Mon Jan  3 14:48:00 2022
```    

# Overflow Epoch times (Y2K38)

```c
time_t currentTime;
currentTime = 0x7FFFFFFF + 1;//total second since Epoch
printf("%s", ctime(&currentTime));
```

This will give warning:

```
main.c:7:30: warning: integer overflow in expression of type ‘int’ results in ‘-2147483648’ [-Woverflow]
    7 |     currentTime = 0x7FFFFFFF + 1;//total second since Epoch
```

**Result**: 

* ``(null)`` (in Ubuntu 20.04)
* ``Fri Dec 13 20:45:52 1901`` (in 5.4.0-xilinx)

# Delay for a number of seconds

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

# Read and write RTC time of /dev/rtc

## Read RTC time

Read RTC time of ``/dev/rtc`` in GMT+7 time zone. For GMT+7, ``tm_hour`` of ``struct rtc_time`` need to add ``+7``.

**Program**: [read_rtc_time.c](read_rtc_time.c)

**Result**

```
Raw read date is 8:3:123
Raw read time is 6:5:36

Current date is 8:4:2023 //April 8th 2023
Current time is 13:5:36 // 01:05:36 PM
```
## Write RTC time

Set date and time to April 23 2022, 00:01:01 AM

**Program**: [write_rtc_time.c](write_rtc_time.c)

**Result**: If setting successfully, check the time and date by [hwclock command](). Restart PC for the RTC time to get back to their realtime date