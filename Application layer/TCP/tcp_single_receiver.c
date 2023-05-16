#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <signal.h> 
#include <sys/mman.h>
#include <sys/wait.h>

#define REUSEADDR
#define MAXPENDING 	5
#define BUFFSIZE 	256
#define PORT 		8000

//Macro for mmap() setup
#define PAGE_SIZE   4048
#define NO_FD       -1  //No file descriptor used for shared memory
#define BASE_ADDR   0   //No specific base address to set in shared memory

int 		sender_fd;
socklen_t 	sender_length;
char 		buffer[BUFFSIZE];
struct 		sockaddr_in sender_addr, receiver_addr;

int         socket_id = 0;
int         *total_connected_sender;

void        sigint_handler(int signal_number);

int         sender_fd_pipe[2];

/*
    Init socket parameters
*/
int socket_init(){
    total_connected_sender = (int *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
    *total_connected_sender = 0;

    //Create TCP socket receiver
    int receiver_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (receiver_fd < 0){
        perror("receiver_fd\n");
    } else printf("Create TCP receiver socket successfully\n");
 
    receiver_addr.sin_family = AF_INET;                
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    receiver_addr.sin_port = htons(PORT);      

    //Bind to the local address
    if (bind(receiver_fd, (struct sockaddr *) &receiver_addr, sizeof(receiver_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start TCP socket receiver successfully through binding\n");

    //Set up connection mode for socket sender
    if (listen(receiver_fd, MAXPENDING) < 0) exit(0);

    sender_length = sizeof(sender_addr);//Get address size of sender
    bzero(buffer, BUFFSIZE);//Delete buffer

    #ifdef REUSEADDR
        int enable_val = 1;
        if (!setsockopt(receiver_fd, SOL_SOCKET, SO_REUSEADDR, &enable_val, sizeof(enable_val))){
            printf("Set socket to reuse address successfully\n");
        } else printf("Unable to set socket to reuse address\n");
    #endif
    return receiver_fd;
}

int main(int argc, char *argv[]){
    signal(SIGINT, sigint_handler);

    int receiver_fd = socket_init();

    // Create a pipe for sender socket fd
    if(pipe(sender_fd_pipe) == -1){
		printf("An error occured when creating a pipe for sender fd\n");
		return 1;
	}

    printf("Waiting for a TCP sender to connect ...\n");
    
    //sender handler
    while(1){
        // wait for sender to connect, return new socket for that sender
        if ((sender_fd = accept(receiver_fd, (struct sockaddr *) &sender_addr, &sender_length)) > 0){
            char ip_str[30];
            inet_ntop(AF_INET, &(sender_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            *total_connected_sender += 1;
            socket_id += 1;
            printf("New TCP sender with fd %d connected with IP %s, %d TCP senders have connected now\n", sender_fd, ip_str, *total_connected_sender);
            
            write(sender_fd_pipe[1], &sender_fd, sizeof(int));

            int pid = fork();
            if (!pid) {
                printf("TCP sender has ID %d\n", socket_id);

                while (1){
                    int bytes_received = read(sender_fd, buffer, BUFFSIZE);
                    if (bytes_received > 0) {
                        printf("Message from TCP sender ID %d: %s", socket_id, buffer);
                        bzero(buffer, BUFFSIZE);         //Delete buffer
                    } 
                    /*
                        else condition includes:
                        1. Right after the TCP socket is disconnected, read() will return 0.
                            If tcp_multiple_senders.c sends empty string, read() won't return 0. 
                        2. socket error, read() returns -1
                    */
                    else {
                        printf("TCP sender with ID %d is disconnected\n", socket_id);
                        *total_connected_sender -= 1;
                        printf("%d TCP senders have connected now\n", *total_connected_sender);
                        close(sender_fd); 
                        kill(getpid(), SIGKILL);
                    }
                }
            } 
        }
    }   
}

/*
    SIGINT signal handler will clean up memory when pressing CTR+C (SIGINT) by:
    * close all senders fd
    * kill all processes (child and parent) in the process group
*/
void sigint_handler(int signal_number){
    close(sender_fd_pipe[1]);

    int *sender_fd_arr = (int*) malloc(*total_connected_sender * sizeof(int));  

    read(sender_fd_pipe[0], sender_fd_arr, *total_connected_sender * sizeof(int));
    close(sender_fd_pipe[0]);

    // kill() pid=0 to kill all processes (child and parent) in the process group
    kill(0, SIGKILL);

    for (int i = 0; i < *total_connected_sender; i++){
        printf("sender_fd_arr[%d] %d\n", i, sender_fd_arr[i]);
        close(sender_fd_arr[i]);
    }
    exit(0);
}