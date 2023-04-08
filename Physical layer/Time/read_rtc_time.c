#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //for open()
#include <sys/ioctl.h>

#include <linux/rtc.h> // For Linux RTC

#define RTC_DEV    "/dev/rtc"

#define GMT07   7 //GMT+7

int rtc;
struct rtc_time rtc_read_time;

int main(int argc, char *argv[]) {
	rtc = open(RTC_DEV, O_RDWR);
	if (rtc){
		if (ioctl(rtc, RTC_RD_TIME, &rtc_read_time) == -1) {
            printf("Fail to open %s\n", RTC_DEV);
        } else {
            printf("Raw read date is %d:%d:%d\n", rtc_read_time.tm_mday, rtc_read_time.tm_mon, rtc_read_time.tm_year);
            printf("Raw read time is %d:%d:%d\n", rtc_read_time.tm_hour, rtc_read_time.tm_min, rtc_read_time.tm_sec);

            printf("Current date is %d:%d:%d\n", rtc_read_time.tm_mday, rtc_read_time.tm_mon+1, rtc_read_time.tm_year + 1900);
            printf("Current time is %d:%d:%d\n", rtc_read_time.tm_hour + GMT07, rtc_read_time.tm_min, rtc_read_time.tm_sec);
        }
	}
}	