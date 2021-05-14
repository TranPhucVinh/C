#include <stdio.h>          /* for printf() and fprintf() */
#include <sys/socket.h>     /* for socket(),connect(),send() and recv() */
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>

#define MAXPENDING 5
#define BUFFSIZE 256
#define PORT 8000

int server_fd, client_fd;
socklen_t clntLen;
char buffer[BUFFSIZE];
struct sockaddr_in serv_addr, cli_addr;

void error(const char *msg){
    perror(msg);
    exit(0);
}
 
int main(int argc, char *argv[]){

    //Create socket server
    if ((server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        error("ERROR opening socket");
    }
 
    serv_addr.sin_family = AF_INET;                
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_addr.sin_port = htons(PORT);      

    // Bind to the local address
    if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Set up connection mode for socket server
    if (listen(server_fd, MAXPENDING) < 0)
        error("ERROR on binding");

    // measure address size of client
    clntLen = sizeof(cli_addr);

    // wait for client to connect, return new socket with client
    if ((client_fd = accept(server_fd, (struct sockaddr *) &cli_addr, &clntLen)) < 0){
        error("accept() failed");
    } else printf("New client connected\n");

    //Delete buffer
    bzero(buffer, BUFFSIZE);

    //Client handler
    while(1){
        recv(client_fd, buffer, BUFFSIZE, 0);
        printf("Received message: %s", buffer);

        bzero(buffer, BUFFSIZE);         //Delete buffer
        
        // n = read(client_fd, buffer, 1024);
        // printf("%s\n", buffer);
    }
}
