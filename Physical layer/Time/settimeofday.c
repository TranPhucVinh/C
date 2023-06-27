#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>

#define TIMEZONE NULL

void get_time_of_day(struct timezone *tz);
void set_time_of_day(struct tm *_tm, struct timezone *tz);

int main() {
    struct tm _tm;
    _tm.tm_sec = 59;
    _tm.tm_min = 30;
    _tm.tm_hour = 12;
    _tm.tm_mday = 31;
    _tm.tm_mon = 11;
    _tm.tm_year = 100;
    _tm.tm_wday = 6;
    _tm.tm_wday = 123;
    _tm.tm_isdst = -1;

    get_time_of_day(NULL);
    set_time_of_day(&_tm, NULL);
    get_time_of_day(NULL);
    return 0;
}

void get_time_of_day(struct timezone *tz){
    struct timeval tv;
    struct tm *_tm;
    time_t unix_time;
    char buffer[64];
    
    gettimeofday(&tv, NULL);
    unix_time = tv.tv_sec;

    _tm = localtime(&unix_time);
    printf("%s", asctime(_tm));
    strftime (buffer, sizeof buffer, "Today is %A, %B %d.\n", _tm);
    printf("%s", buffer);
    strftime (buffer, sizeof buffer, "The time is %I:%M %p.\n", _tm);
    printf("%s",buffer);
}

void set_time_of_day(struct tm *_tm, struct timezone *tz){
    struct timeval tv;
    time_t unix_time;
    unix_time = mktime(_tm);//Convert human readable date time to Unix time
    tv.tv_sec = unix_time;
    tv.tv_usec= 0;

    int ret = settimeofday(&tv, tz);
    if(!ret) {
        printf("Set time of day successfully\n");
    }
    else {
        printf("Fail to set of day\n");
        if (errno == EPERM) printf("Don't have permission to set time\n");
        else if (errno == EINVAL) printf("Invalid argument\n");
        else printf("%d", errno);
    }
}