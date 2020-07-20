### Server

```c
#include <stdio.h>          /* for printf() and fprintf() */
#include <sys/socket.h>     /* for socket(),connect(),send() and recv() */
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <sys/types.h> 
#include <netinet/in.h>
#define MAXPENDING 5
#define BUFFSIZE 256
#define PORT 8888
 
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
 
int main(int argc, char *argv[]){
    int servSock, clntfd, n;
    socklen_t clntLen;
    char buffer[BUFFSIZE];
    struct sockaddr_in serv_addr, cli_addr;

    // Tao socket server
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        error("ERROR opening socket");

    // Ghi cau truc dia chi
    memset(&serv_addr, 0, sizeof(serv_addr));       
    serv_addr.sin_family = AF_INET;                
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv_addr.sin_port = htons(PORT);         
    
    // Bind to the local address
    if (bind(servSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // thiet lap che do cho ket noi cho socket server
    if (listen(servSock, MAXPENDING) < 0)
        error("ERROR on binding");

    // do kich thuoc dia chi cua client
    clntLen = sizeof(cli_addr);

    // cho doi client ket noi, tra ve socket moi ket noi voi client
    if ((clntfd = accept(servSock, (struct sockaddr *) &cli_addr, &clntLen)) < 0)
        error("accept() failed");

    // xoa buffer
    bzero(buffer,BUFFSIZE);
    // xu ly voi client
    while(1){
        n = recv(clntfd,buffer,BUFFSIZE,0);
        if ( n<0 ) error("ERROR reading from socket");
        else printf("%d", n);
    }
}            
```

### client.c

```c
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
 
#define BUFFSIZE 256
#define PORT 8888
 
void error(const char *msg){
    perror(msg);
    exit(0);
}
 
int main(int argc, char *argv[]){
    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[BUFFSIZE];
    char *servIP;
 
    if(argc < 2){
        fprintf(stderr, "Hay nhap: %s <Server IP> \n",argv[0]);
        exit(1);
    }
    servIP = argv[1];       // localhost : "127.0.0.1"
 
    // Tao socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        error("socket() failed");
 
    // Ghi cau truc dia chi cho server
    memset(&serv_addr, 0, sizeof(serv_addr));               
    serv_addr.sin_family      = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(servIP);          
    serv_addr.sin_port        = htons(PORT);
 
    // Ket noi toi server
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) 
        error("ERROR connecting");
 
    // Gui du lieu
    while(1){
        printf("message: ");
        bzero(buffer,BUFFSIZE);
        fgets(buffer,BUFFSIZE,stdin);
        if ( send(sockfd,buffer,strlen(buffer)-1,0) < 0) 
            error("ERROR writing to socket");
    }
    // Dong client
    close(sockfd);
    return 0;
}
```
