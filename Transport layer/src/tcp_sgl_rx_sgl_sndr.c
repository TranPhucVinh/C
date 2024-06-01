#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */

#define REUSEADDR
#define MAXPENDING 	1
#define BUFFSIZE 	256
#define PORT 		8000

int         socket_param_init(int port);

int main() {
    int 		receiver_fd, sender_fd;
    struct 		sockaddr_in sender_addr;
    socklen_t 	sender_length = sizeof(sender_addr);//Get address size of sender

    receiver_fd = socket_param_init(PORT);

    printf("Waiting for a TCP sender to connect ...\n");
    
    //sender handler
    while(1){
        // wait for sender to connect, return new socket for that sender
        if ((sender_fd = accept(receiver_fd, (struct sockaddr *) &sender_addr, &sender_length)) > 0){
            char ip_str[30];
            inet_ntop(AF_INET, &(sender_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            printf("TCP sender with fd %d connected with IP %s\n", sender_fd, ip_str);

            while (1){
                char buffer[BUFFSIZE];
                bzero(buffer, BUFFSIZE);//Delete buffer
                int bytes_received = read(sender_fd, buffer, BUFFSIZE);
                if (bytes_received > 0) {
                    printf("Message from TCP sender: %s", buffer);
                    bzero(buffer, BUFFSIZE);         //Delete buffer
                } 
                /*
                    else condition includes:
                    1. Right after the connected TCP socket is disconnected, read() will return 0.
                       If tcp_sgl_sndr_sgl_rx.c sends empty string, read() won't return 0. 
                    2. socket error, read() returns -1
                */
                else {
                    printf("TCP sender has disconnected. Stop TCP receiver, too \n");
                    close(sender_fd); 
                    exit(0);
                }
            }
        }
    }   
}

/*
    Init socket parameters
*/
int socket_param_init(int port){
    struct sockaddr_in receiver_addr;

    // Create TCP socket receiver
    int receiver_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (receiver_fd < 0){
        perror("receiver_fd\n");
    } else printf("Create TCP receiver socket successfully\n");
 
    receiver_addr.sin_family = PF_INET;                
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    receiver_addr.sin_port = htons(port);      

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

    // Set up connection mode for socket sender. listen() allows this
    // TCP receiver program to listen to connection from the TCP senders
    if (listen(receiver_fd, MAXPENDING) < 0) exit(0);

    return receiver_fd;
}