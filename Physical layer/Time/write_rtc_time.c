#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h> //for open()
#include <sys/ioctl.h>

#include <linux/rtc.h> // For Linux RTC

#define RTC_DEV    "/dev/rtc"

#define GMT07   7 //GMT+7

int rtc;
struct rtc_time rtc_set_time;

int main(int argc, char *argv[]) {
    int day = 8, month = 8, year = 2023;
    int hour = 13, minute = 1, second = 1;
    
    rtc_set_time.tm_mday = day;
    rtc_set_time.tm_mon = month - 1;
    rtc_set_time.tm_year = year - 1900;

    rtc_set_time.tm_hour = hour - GMT07;
    rtc_set_time.tm_min = minute;
    rtc_set_time.tm_sec = second;

	rtc = open(RTC_DEV, O_RDWR);
	if (rtc){
		if (ioctl(rtc, RTC_SET_TIME, &rtc_set_time) == -1) {
            printf("Fail to open %s\n", RTC_DEV);
			printf("%d\n", errno);
        } else {
            printf("Set date and time successfully, use hwclock() command to check\n");            
        }
	}
}		