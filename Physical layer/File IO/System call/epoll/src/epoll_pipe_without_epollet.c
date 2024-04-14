#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

#define TIMEOUT     5000    //miliseconds
#define BUFF_SIZE   10
#define MAXEVENTS   1       //1 event for EPOLLIN

struct epoll_event monitored_event[1], happened_event[1];

int main(int argc, char *argv[])  {
	int fd[2];
	if(pipe(fd) == -1){
		printf("An error occured when opening the pipe\n");
		return 1;
	}

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    }

    monitored_event[0].events = EPOLLIN;
    monitored_event[0].data.fd = fd[0];//fd[0] of pipe
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd[0], monitored_event) < 0){
        printf("Unable to add current opening terminal STDIN_FILENO to be monitored by epoll\n");
        return 0;
    }

	int pid = fork();
	if (!pid) {
        char snd_str[] = "Hello, World !";
        write(fd[1], snd_str, sizeof(snd_str));
    }	
    else {
        while (1){
            int epollret = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
            if (epollret == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
            else if (epollret > 0){
                char rcv_str[50];
                memset(rcv_str, 0, sizeof(rcv_str));
                read(fd[0], rcv_str, 1);
                if (happened_event[0].events == EPOLLIN) {
                    printf("%s\n", rcv_str);
                }
            }
            else {
                printf("epoll_wait error %d\n", epollret);        
                close(epfd);
                return -1;
            }
        }
    }	
    close(fd[1]);
    close(fd[0]);
}