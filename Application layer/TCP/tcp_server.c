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

int 		server_fd, client_fd;
socklen_t 	clntLen;
char 		buffer[BUFFSIZE];
struct 		sockaddr_in serv_addr, cli_addr;

int         socket_id = 0;
int         *total_connected_client;

void socket_parameter_init(){
    total_connected_client = (int *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
    *total_connected_client = 0;

    //Create socket server
    if ((server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("tcp_server\n");
    } else printf("Create socket successfully\n");
 
    serv_addr.sin_family = AF_INET;                
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_addr.sin_port = htons(PORT);      

    //Bind to the local address
    if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start TCP socket server successfully through binding\n");

    //Set up connection mode for socket server
    if (listen(server_fd, MAXPENDING) < 0) exit(0);

    clntLen = sizeof(cli_addr);//Get address size of client
    bzero(buffer, BUFFSIZE);//Delete buffer
}

int main(int argc, char *argv[]){
    socket_parameter_init();

    printf("Waiting for a TCP client to connect ...\n");
    
    //Client handler
    while(1){
        // wait for client to connect, return new socket with client
        if ((client_fd = accept(server_fd, (struct sockaddr *) &cli_addr, &clntLen)) > 0){
            char ip_str[30];
            // now get it back and print it
            inet_ntop(AF_INET, &(cli_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            *total_connected_client += 1;
            socket_id += 1;
            printf("New tcp client connected with IP %s, %d TCP clients have connected now\n", ip_str, *total_connected_client);

            int pid = fork();
            if (!pid) { 
                printf("TCP client has ID %d\n", socket_id);
                while (1){
                    int bytes_received = read(client_fd, buffer, BUFFSIZE);
                    if (bytes_received > 0) {
                        printf("Message from TCP client ID %d: %s", socket_id, buffer);
                        bzero(buffer, BUFFSIZE);         //Delete buffer
                    } 
                    /*
                        Right after the TCP socket is disconnected, read() will return 0.
                        If tcp_client.c sends empty string, read() won't return 0. 
                    */
                    else if (bytes_received == 0) {
                        printf("TCP client with ID %d is disconnected\n", socket_id);
                        *total_connected_client -= 1;
                        printf("%d TCP clients have connected now\n", *total_connected_client);
                        kill(getpid(), SIGKILL);
                    }
                }
            } 
        }
    }   
}
