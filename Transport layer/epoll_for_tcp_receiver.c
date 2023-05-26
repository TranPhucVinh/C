#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/epoll.h>

#define REUSEADDR
#define MAXPENDING 	5
#define BUFFSIZE 	256
#define MAXEVENTS   1       //1 event for EPOLLIN
#define PORT 		8000

#define TIMEOUT     5000    //miliseconds

int         socket_init();
struct      epoll_event monitored_event[1], happened_event[1];

int main(){
    struct 		sockaddr_in sender_addr;
    socklen_t 	sender_length;
    char        ip_str[30];
    int         receiver_fd, sender_fd;

    sender_length = sizeof(sender_addr);//Get address size of sender

    receiver_fd = socket_init();

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    } else {
        printf("Waiting for a TCP sender to connect ...\n");
        while (1){
            if ((sender_fd = accept(receiver_fd, (struct sockaddr *) &sender_addr, &sender_length)) > 0){
                inet_ntop(AF_INET, &(sender_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
                printf("New TCP sender with fd %d connected with IP %s\n", sender_fd, ip_str);

                monitored_event[0].events = EPOLLIN;
                monitored_event[0].data.fd = sender_fd;//Add file descriptor sender_fd to monitor

                if (epoll_ctl(epfd, EPOLL_CTL_ADD, sender_fd, monitored_event) < 0){
                    printf("Unable to add current opening terminal STDIN_FILENO to be monitored by epoll\n");
                    return 0;
                } else {
                    while (1){
                        int epollret = epoll_wait(epfd, happened_event, MAXEVENTS, TIMEOUT);
                        if (epollret == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
                        else if (epollret > 0){
                            char 		buffer[BUFFSIZE];
                            bzero(buffer, BUFFSIZE);//Delete buffer
                            if (happened_event[0].events == EPOLLIN) {
                                int bytes_received = read(sender_fd, buffer, BUFFSIZE);
                                if (bytes_received > 0) printf("Message from TCP sender: %s", buffer);
                                else {
                                    // If the connected TCP sender disconnects, break while(1) loop to wait
                                    // for another TCP sender to connect
                                    printf("TCP sender with fd %d and IP %s is disconnected\n", sender_fd, ip_str);
                                    close(sender_fd); 
                                    break;
                                }
                            }
                        } else {
                            printf("epoll_wait error %d\n", epollret);        
                            close(epfd);
                            return -1;
                        }
                    }
                }
            }   
        }
    }
    return 1;
}

/*
    Init socket parameters
*/
int socket_init(){
    struct 	sockaddr_in receiver_addr;
    
    //Create TCP socket receiver
    int receiver_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (receiver_fd < 0){
        perror("receiver_fd\n");
    } else printf("Create TCP receiver socket successfully\n");
 
    receiver_addr.sin_family = AF_INET;                
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    receiver_addr.sin_port = htons(PORT);      

    // setsockopt() must be called before bind() so that SO_REUSEADDR can take effect
    #ifdef REUSEADDR
        int enable_val = 1;
        if (!setsockopt(receiver_fd, SOL_SOCKET, SO_REUSEADDR, &enable_val, sizeof(enable_val))){
            printf("Set socket to reuse address successfully\n");
        } else printf("Unable to set socket to reuse address\n");
    #endif

    //Bind to the local address
    if (bind(receiver_fd, (struct sockaddr *) &receiver_addr, sizeof(receiver_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start TCP socket receiver successfully through binding\n");

    //Set up connection mode for socket sender
    if (listen(receiver_fd, MAXPENDING) < 0) exit(0);

    return receiver_fd;
}