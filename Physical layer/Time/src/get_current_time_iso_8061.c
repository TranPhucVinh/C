#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define TIMEZONE NULL

void get_time_of_day(struct timezone *tz);

int main() {
    get_time_of_day(NULL);
    return 0;
}

void get_time_of_day(struct timezone *tz){
    struct timeval tv;
    struct tm *_tm;
    time_t _localtime;
    char buffer[64];
    
    gettimeofday(&tv, NULL);
    _localtime = tv.tv_sec;

    _tm = localtime(&_localtime);
    printf("%s", asctime(_tm));
    strftime(buffer, sizeof buffer, "Today is %A, %B %d.\n", _tm);
    printf("%s", buffer);
    strftime(buffer, sizeof buffer, "The time is %I:%M %p.\n", _tm);
    printf("%s",buffer);
    strftime(buffer, sizeof buffer, "%Y%m%dT%H%M%SZ", _tm);
    printf("ISO 8061 %s",buffer);
}