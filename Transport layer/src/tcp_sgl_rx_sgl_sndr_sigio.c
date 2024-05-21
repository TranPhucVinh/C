#include <stdio.h>          
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for bzero() */
#include <signal.h>   
#include <fcntl.h>  
#include <unistd.h>         /* for close() */

#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <sys/socket.h>     /* for socket(), connect()*/

#define REUSEADDR
#define MAXPENDING 	1
#define BUFFSIZE 	256
#define PORT 		8000

int         socket_param_init(int port);
void        sigio_setup_for_sndr_socket(int sndr_fd, void (*sigio_handler)(int sig_num));
void        sigio_handler(int sig_num);

int         sndr_fd_sigio;

int main() {
    int         sndr_fd, rx_fd;
    struct 		sockaddr_in sender_addr;
    socklen_t 	sender_length = sizeof(sender_addr);//Get address size of sender

    rx_fd = socket_param_init(PORT);

    printf("Waiting for a TCP sender to connect ...\n");
    
    while(1){
        // wait for sender to connect, return new socket for that sender
        if ((sndr_fd = accept(rx_fd, (struct sockaddr *) &sender_addr, &sender_length)) > 0){
            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(sender_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            printf("TCP sender with fd %d connected with IP %s\n", sndr_fd, ip_str);

            sndr_fd_sigio = sndr_fd;
            sigio_setup_for_sndr_socket(sndr_fd_sigio, sigio_handler);

            while(1){
                pause();
            }
        }
    }
}

void sigio_setup_for_sndr_socket(int sndr_fd, void (*sigio_handler)(int sig_num)) {
    struct sigaction sa;
    int flags;

    // Set up the SIGIO signal handler
    sa.sa_handler = sigio_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGIO, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Get the file descriptor flags
    if ((flags = fcntl(sndr_fd, F_GETFL)) == -1) {
        perror("fcntl(F_GETFL)");
        exit(EXIT_FAILURE);
    }

    // Set the file descriptor to non-blocking mode
    if (fcntl(sndr_fd, F_SETFL, flags | O_NONBLOCK | O_ASYNC) == -1) {
        perror("fcntl(F_SETFL)");
        exit(EXIT_FAILURE);
    }

    // Set the process to receive SIGIO signals for the file descriptor
    if (fcntl(sndr_fd, F_SETOWN, getpid()) == -1) {
        perror("fcntl(F_SETOWN)");
        exit(EXIT_FAILURE);
    }
}

void sigio_handler(int sig_num) {
    int sndr_fd = sndr_fd_sigio;

    char buffer[BUFFSIZE];
    bzero(buffer, BUFFSIZE);//Delete buffer
    int bytes_received = read(sndr_fd, buffer, BUFFSIZE);
    if (bytes_received > 0) {
        write(STDOUT_FILENO, buffer, BUFFSIZE);
        bzero(buffer, BUFFSIZE);         //Delete buffer
    } 
    /*
        else condition includes:
        1. Right after the connected TCP socket is disconnected, read() will return 0.
            If tcp_sgl_sndr_sgl_rx.c sends empty string, read() won't return 0. 
        2. socket error, read() returns -1
    */
    else {
        char disconnected_str[] = "TCP sender has disconnected. Stop TCP receiver, too \n";
        write(STDOUT_FILENO, disconnected_str, sizeof(disconnected_str));
        close(sndr_fd); 
        exit(EXIT_FAILURE);
    }
}

/*
    Init socket parameters
*/
int socket_param_init(int port){
    struct sockaddr_in receiver_addr;

    // Create TCP socket receiver
    int rx_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (rx_fd < 0){
        perror("rx_fd\n");
    } else printf("Create TCP receiver socket successfully\n");
 
    receiver_addr.sin_family = PF_INET;                
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    receiver_addr.sin_port = htons(port);      

    // setsockopt() must be called before bind() so that SO_REUSEADDR can take effect
    #ifdef REUSEADDR
        int enable_val = 1;
        if (!setsockopt(rx_fd, SOL_SOCKET, SO_REUSEADDR, &enable_val, sizeof(enable_val))){
            printf("Set socket to reuse address successfully\n");
        } else printf("Unable to set socket to reuse address\n");
    #endif

    //Bind to the local address
    if (bind(rx_fd, (struct sockaddr *) &receiver_addr, sizeof(receiver_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start TCP socket receiver successfully through binding\n");

    // Set up connection mode for socket sender. listen() allows this
    // TCP receiver program to listen to connection from the TCP senders
    if (listen(rx_fd, MAXPENDING) < 0) exit(0);

    return rx_fd;
}
