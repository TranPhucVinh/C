#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <linux/input-event-codes.h>// REL_X, REL_Y

#define MOUSE_INPUT_EVENT   "/dev/input/event19"

struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    signed value;
};

void main(void)
{
    int fd, fsize;
    char buff[128];
    struct input_event *temp;
    signed x, y;
    x = y = 0;
    fd = open(MOUSE_INPUT_EVENT, O_RDONLY);
    if (fd >0){
        while (1)
        {
            fsize = (int)read(fd, buff, 1024);
            if (fsize > 0)
            {
                temp = (struct input_event *)buff;
                if (temp->code == REL_X) x = temp->value;// X-axis
                else if (temp->code == REL_Y) y = temp->value;// Y-axis
            }
            printf("x=%d y=%d\n", x, y);
        }
    } else printf("%d\n", fd);
}
