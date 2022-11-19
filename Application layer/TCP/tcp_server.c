#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect(), send() and recv() */
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */

#define MAXPENDING 	5
#define BUFFSIZE 	256
#define PORT 		8000

int 		server_fd, client_fd;
socklen_t 	clntLen;
char 		buffer[BUFFSIZE];
struct 		sockaddr_in serv_addr, cli_addr;

int         socket_id = 0;
int         total_connected_client = 0;

void socket_parameter_init(){
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
            total_connected_client += 1;
            printf("New tcp client connected with IP %s, %d TCP clients have connected\n", ip_str, total_connected_client);

            int pid = fork();
            if (!pid) {
                socket_id += 1;
                while (1){
                    int bytes_received = recv(client_fd, buffer, BUFFSIZE, 0);
                    if (bytes_received) {
                        printf("Message from TCP client ID %d: %s", socket_id, buffer);
                        bzero(buffer, BUFFSIZE);         //Delete buffer
                    }
                    // n = read(client_fd, buffer, 1024);
                    // printf("%s\n", buffer);
                }
            } 
        }
    }   
}
