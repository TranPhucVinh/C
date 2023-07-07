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

#include <vector>
#include <algorithm> //find()

#define REUSEADDR
#define MAXPENDING 	5
#define BUFFSIZE 	256
#define MAXEVENTS   1       // Maximum number connected TCP senders to handle/monitor
#define PORT 		8000

#define TIMEOUT     5000    // miliseconds

int         socket_parameter_init();
struct      epoll_event sender_connect_event;// New TCP sender connection event
struct      epoll_event happened_events[MAXEVENTS];

int main(){
    struct 		sockaddr_in sender_addr;
    socklen_t 	sender_length;
    char        ip_str[30];
    int         receiver_fd;
    std::vector<int> tcp_senders_fd_list;

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    }

    sender_length = sizeof(sender_addr);//Get address size of sender
    receiver_fd = socket_parameter_init();

    sender_connect_event.events  = EPOLLIN;
    sender_connect_event.data.fd = receiver_fd;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, receiver_fd, &sender_connect_event)){
        printf("Failed to add receiver_fd to be monitored by epoll");
        close(receiver_fd);
        return 1;
    }

    printf("Waiting for a TCP sender to connect ...\n");
    while (1){
        /*
            ready_socket_fds: Total ready TCP socket file descriptors
            Those TCP sockets can be both TCP receiver and senders
        */
        int ready_socket_fds = epoll_wait(epfd, happened_events, MAXEVENTS, TIMEOUT);
        if (ready_socket_fds == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
        else {
            /*
                By using while(1) and this for() loop, happened_events() is updated in 
                everytime the EPOLLIN happens to TCP receiver and TCP senders

            */
            for(int i = 0; i < ready_socket_fds; i++){
                int socket_fd = happened_events[i].data.fd;

                /*
                    A new TCP sender connects to TCP receiver will trigger
                    the EPOLLIN event in that TCP receiver
                */
                if(socket_fd == receiver_fd){
                    int sender_fd;
                    if ((sender_fd = accept(receiver_fd, (struct sockaddr *) &sender_addr, &sender_length)) > 0){
                        inet_ntop(AF_INET, &(sender_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
                        printf("New TCP sender with fd %d connected with IP %s\n", sender_fd, ip_str);

                        struct epoll_event tcp_sender_event;// epoll_event to monitor the newly connected TCP sender
                        tcp_sender_event.events = EPOLLIN;
                        tcp_sender_event.data.fd = sender_fd;//Add file descriptor sender_fd to monitor

                        // Add that tcp_sender_event to be monitored by epoll
                        if (epoll_ctl(epfd, EPOLL_CTL_ADD, sender_fd, &tcp_sender_event) < 0){
                            printf("Unable to add fd of the connected TCP sender to be monitored by epoll\n");
                        } else {
                            tcp_senders_fd_list.push_back(sender_fd);
                            printf("Succesfully add TCP sender fd %d to monitored list\n", sender_fd);
                            printf("Totally %ld TCP senders are connected now\n", tcp_senders_fd_list.size());
                        }
                    }
                }

                /*
                    Any connected TCP sender writes data to TCP receiver
                    will trigger the EPOLLIN event in that TCP receiver
                */
                else {
                    char buffer[BUFFSIZE];
                    bzero(buffer, BUFFSIZE);//Delete buffer
                    int bytes_received = read(socket_fd, buffer, BUFFSIZE);
                    if (bytes_received > 0) printf("Message from TCP sender with fd %d: %s", socket_fd, buffer);
                    else {
                        auto pos = find(tcp_senders_fd_list.begin(), tcp_senders_fd_list.end(), socket_fd);
                        if(pos != tcp_senders_fd_list.end()){
                            tcp_senders_fd_list.erase(pos);
                        }
                        epoll_ctl(epfd, EPOLL_CTL_DEL, socket_fd, NULL);
                        printf("TCP sender with fd %d and IP %s is disconnected\n", socket_fd, ip_str);
                        printf("Totally %ld TCP senders are connected now\n", tcp_senders_fd_list.size());
                        close(socket_fd); 
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
int socket_parameter_init(){
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