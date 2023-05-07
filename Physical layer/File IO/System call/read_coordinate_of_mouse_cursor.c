#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MOUSE_INPUT_EVENT   "/dev/input/event19"

struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

void main(void)
{
    int fd, fsize;
    char buff[128];
    struct input_event *temp;
    unsigned int x, y;
    x = y = 0;
    fd = open(MOUSE_INPUT_EVENT, O_RDONLY);//mouse
    if (fd >0){
        while (1)
        {
            fsize = (int)read(fd, buff, 1024);
            if (fsize > 0)
            {
                temp = (struct input_event *)buff;
                if (temp->code == 0)
                x = temp->value;
                else
                y = temp->value;
            }
            printf("x=%u y=%u\n", x, y);
        }
    } else printf("%d\n", fd);
}