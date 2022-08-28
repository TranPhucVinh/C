#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char buffer[1024];
#define MAX_EVENTS 10
int epollfd, fd;
bool isMultipleLine = false;
void signal_action_handler(int signal_number, siginfo_t *siginfo, void *ucontext){
    close(fd);
    close(epollfd);
    exit(0);
}

int main(int argc, char** args)
{

    if (argc > 2)
    {
        printf("Too many arguments\n");
        exit(1);
    }
    if (argc == 2)
    {
        if (strcmp(args[1], "-m") == 0)
        {
            isMultipleLine = true;
        }
        else if(strcmp(args[1], "--help") == 0 || strcmp(args[1], "-h") == 0)
        {
            printf("Usage: kmess [OPTION]\n");
            printf(" -h, --help     Get help for the command\n");
            printf(" -m             Some kernel message is multi-lines, use this to display full msg\n");
            printf("                1 line displayed is default\n");
            exit(0);
        }
        else
        {
            printf("Invalid arguments\n");
            exit(1);
        }
    }

    struct sigaction sa;
    sa.sa_sigaction = &signal_action_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    fd = open("/dev/kmsg", O_RDONLY|O_NONBLOCK);
    if (fd < 0)
    {
        printf("fail to open\n");
        return -1;
    }

    // need this to fetch the latest update
    lseek(fd, 0, SEEK_END);

    struct epoll_event ev, events[MAX_EVENTS];
    int nfds;

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = fd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        perror("Fail to init epoll\n");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        bzero(buffer, 1024);
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            close(epollfd);
            exit(EXIT_FAILURE);
        }
        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == fd) {
                int sz = read(fd, buffer, 1024);
                // the format will be sth like this
                // 4,516,1452858886,-;<kernel message>
                // string process
                char* content_msg = strstr(buffer, ";") + 1;
                char* num_str = strtok(buffer, ";");

                char* time_str = strtok(num_str, ",");
                time_str = strtok(NULL, ",");
                time_str = strtok(NULL, ",");
                long long ret = atoll(time_str);
                double time_s = ret / 1000000.0;

                // final printf
                if (isMultipleLine)
                {
                    printf("[ %.6lf] %s", time_s, content_msg);
                }
                else
                {
                    printf("[ %.6lf] %s\n", time_s, strtok(content_msg, "\n"));
                }
            } else {
                // weird behavior
                close(epollfd);
                exit(1);
            }
        }
    }

    // program cannot get here
    return 0;
}