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

#define MAXPENDING 	5
#define BUFFSIZE 	256
#define PORT 		8000

//Macro for mmap() setup
#define PAGE_SIZE   4048
#define NO_FD       -1  //No file descriptor used for shared memory
#define BASE_ADDR   0   //No specific base address to set in shared memory

#define NRC         "NRC"//New Receiver Connected: Flag to indicate a new TCP receiver is connected

int 		sender_fd, receiver_fd;
socklen_t 	receiver_length;
char 		buffer[BUFFSIZE];
struct 		sockaddr_in sender_addr, receiver_addr;

int         socket_id = 0;
int         *total_connected_receiver;

char        responded_str[50];

void socket_parameter_init(){
    total_connected_receiver = (int *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
    *total_connected_receiver = 0;

    //Create TCP socket sender
    if ((sender_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("tcp_sender\n");
    } else printf("Create TCP sender socket successfully\n");
 
    sender_addr.sin_family = AF_INET;                
    sender_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    sender_addr.sin_port = htons(PORT);      

    //Bind to the local address
    if (bind(sender_fd, (struct sockaddr *) &sender_addr, sizeof(sender_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start TCP socket sender successfully through binding\n");

    //Set up connection mode for socket sender
    if (listen(sender_fd, MAXPENDING) < 0) exit(0);

    receiver_length = sizeof(receiver_addr);//Get address size of sender
    bzero(buffer, BUFFSIZE);//Delete buffer
}

int main(int argc, char *argv[]){
    socket_parameter_init();

    printf("Waiting for a TCP receiver to connect ...\n");
    
    //Receiver handler
    while(1){
        //Wait for receiver to connect, return new socket for that receiver
        if ((receiver_fd = accept(sender_fd, (struct sockaddr *) &receiver_addr, &receiver_length)) > 0){
            char ip_str[30];
            // now get it back and print it
            inet_ntop(AF_INET, &(receiver_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            *total_connected_receiver += 1;
            socket_id += 1;
            printf("New TCP receiver connected with IP %s, %d TCP receivers have connected now\n", ip_str, *total_connected_receiver);

            int pid = fork();
            if (!pid) { 
                printf("TCP receiver has ID %d\n", socket_id);
                while (1){
                    int bytes_received = read(receiver_fd, buffer, BUFFSIZE);
                    if (bytes_received > 0) {
                        if (!strcmp(buffer, NRC)) {
                            sprintf(responded_str, "String responded to TCP receiver ID %d", socket_id);
                            write(receiver_fd, responded_str, sizeof(responded_str));
                        }
                        bzero(buffer, BUFFSIZE);         //Delete buffer
                    } 
                    
                    /*
                        Right after the TCP socket is disconnected, read() will return 0.
                        If tcp_multiple_senders.c sends empty string, read() won't return 0. 
                    */
                    else if (bytes_received == 0) {
                        printf("TCP receiver with ID %d is disconnected\n", socket_id);
                        *total_connected_receiver -= 1;
                        printf("%d TCP receivers have connected now\n", *total_connected_receiver);
                        kill(getpid(), SIGKILL);
                    }
                }
            } 
        }
    }   
}