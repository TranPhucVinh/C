#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define BUFFSIZE 256
#define PORT 8888

int sockfd, n;
struct sockaddr_in serv_addr;
char buffer[BUFFSIZE];
char *servIP;

void error(const char *msg){
    perror(msg);
    exit(0);
}
 
int main(){
    servIP = "192.168.0.103";
            
    serv_addr.sin_family      = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(servIP);          
    serv_addr.sin_port        = htons(PORT);

    // Create TCP socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        error("socket() failed");
    } else printf("create TCP socket success \n");

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        error("ERROR connecting");
    } else printf("connect to server success \n");

    // Send data
    while(1){
        printf("message: ");
        bzero(buffer, BUFFSIZE);
        fgets(buffer, BUFFSIZE, stdin);

        write(sockfd, buffer, BUFFSIZE);

        // if (send(sockfd, buffer, strlen(buffer)-1, 0) < 0) 
        //     error("ERROR writing to socket");
        // else printf("finish writing: %s", buffer);    
    }

    close(sockfd); //Close socket
    return 0;
}