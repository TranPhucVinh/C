#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <fcntl.h>          /* for open() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/epoll.h>

#include <vector>
#include <algorithm> // find()

#define REUSEADDR
#define MAXPENDING 	5
#define BUFFSIZE 	256
#define MAXEVENTS   1       // Maximum numbers of connected HTTP clients to handle/monitor
#define PORT 		8000

#define TIMEOUT     5000    // miliseconds

int         socket_parameters_init();
struct      epoll_event http_client_conn_evt;// New HTTP client connected event
struct      epoll_event happened_events[MAXEVENTS];

const char *httpd_hdr_str = "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n";

int main(){
    struct 		        sockaddr_in http_client_addr;
    socklen_t 	        http_client_length;
    char                ip_str[30];
    int                 http_server_fd;
    std::vector<int>    http_client_fd_list;

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        printf("Unable to create an epoll fd\n");
        return 0;
    }

    http_client_length = sizeof(http_client_addr);//Get address size of sender
    http_server_fd = socket_parameters_init();

    http_client_conn_evt.events  = EPOLLIN;
    http_client_conn_evt.data.fd = http_server_fd;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, http_server_fd, &http_client_conn_evt)){
        printf("Failed to add http_server_fd to be monitored by epoll");
        close(http_server_fd);
        return 1;
    }

    printf("Waiting for a HTTP client to connect ...\n");
    while (1){
        /*
            ready_socket_fds: Total ready TCP socket file descriptors
            Those TCP sockets can be both HTTP server and senders
        */
        int ready_socket_fds = epoll_wait(epfd, happened_events, MAXEVENTS, TIMEOUT);
        if (ready_socket_fds == 0) printf("Timeout after %d miliseconds\n", TIMEOUT);
        else {
            /*
                By using while(1) and this for() loop, happened_events() is updated in 
                everytime the EPOLLIN happens to HTTP server and HTTP clients

            */
            for(int i = 0; i < ready_socket_fds; i++){
                int socket_fd = happened_events[i].data.fd;

                /*
                    A new HTTP client connects to HTTP server will trigger
                    the EPOLLIN event in that HTTP server
                */
                if(socket_fd == http_server_fd){
                    int http_client_fd;
                    if ((http_client_fd = accept(http_server_fd, (struct sockaddr *) &http_client_addr, &http_client_length)) > 0){
                        inet_ntop(AF_INET, &(http_client_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
                        printf("New HTTP client with fd %d connected with IP %s\n", http_client_fd, ip_str);

                        struct epoll_event http_client_event;// epoll_event to monitor the newly connected HTTP client
                        http_client_event.events = EPOLLIN;
                        http_client_event.data.fd = http_client_fd;//Add file descriptor http_client_fd to monitor

                        // Add that http_client_event to be monitored by epoll
                        if (epoll_ctl(epfd, EPOLL_CTL_ADD, http_client_fd, &http_client_event) < 0){
                            printf("Unable to add fd of the connected HTTP client to be monitored by epoll\n");
                        } else {
                            http_client_fd_list.push_back(http_client_fd);
                            printf("Succesfully add HTTP client fd %d to monitored list\n", http_client_fd);
                            printf("Totally %ld HTTP clients are connected now\n", http_client_fd_list.size());
                        }
                    }
                }

                // Any connected HTTP client writes data to HTTP server will trigger the EPOLLIN event in that HTTP server
                else {
                    char tmp_buf[BUFFSIZE];// Temporary buffer to read index.html
                    char req_buf[BUFFSIZE];// Buffer for HTTP request from HTTP client
                    char res_buf[BUFFSIZE];// Buffer for HTTP response for HTTP client

                    bzero(tmp_buf, BUFFSIZE);//Delete buffer
                    bzero(req_buf, BUFFSIZE);//Delete buffer
                    bzero(res_buf, BUFFSIZE);//Delete buffer

                    int bytes_received = read(socket_fd, req_buf, BUFFSIZE);
                    if (bytes_received > 0) {
                        printf("Message from HTTP client with socket fd %d: %s", socket_fd, req_buf);
                        char* method = strtok(req_buf, " ");
                        char* uri    = strtok(NULL, " ");

                        if(!strcmp(method, "GET")){
                            if(!strcmp(uri, "/")){
                                int fd = open("index.html", O_RDONLY);
                                if (fd > 0){
                                    int sz = read(fd, tmp_buf, BUFFSIZE);
                                    snprintf(res_buf, BUFFSIZE, httpd_hdr_str, "200 OK", "text/html", sz);
                                    strcat(res_buf, "\r\n");
                                    strcat(res_buf, tmp_buf);
                                    write(socket_fd, res_buf, BUFFSIZE);
                                } else {
                                    char no_file[] = "There is no index.html file";
                                    snprintf(res_buf, BUFFSIZE, httpd_hdr_str, "200 OK", "text/html", sizeof(no_file));
                                    strcat(res_buf, "\r\n");
                                    strcat(res_buf, no_file);
                                    printf("%s\n", res_buf);
                                    write(socket_fd, res_buf, BUFFSIZE);
                                }
                            }
                            else {
                                int sz = sprintf(tmp_buf, "Not found %s", uri);
                                snprintf(res_buf, BUFFSIZE, httpd_hdr_str, "200 OK", "text/html", sz);
                                strcat(res_buf, "\r\n");
                                strcat(res_buf, tmp_buf);
                                write(socket_fd, res_buf, BUFFSIZE);
                            }
                        }
                    }
                    else {
                        auto pos = find(http_client_fd_list.begin(), http_client_fd_list.end(), socket_fd);
                        if(pos != http_client_fd_list.end()){
                            http_client_fd_list.erase(pos);
                        }
                        epoll_ctl(epfd, EPOLL_CTL_DEL, socket_fd, NULL);
                        printf("HTTP client with fd %d and IP %s is disconnected\n", socket_fd, ip_str);
                        printf("Totally %ld HTTP clients are connected now\n", http_client_fd_list.size());
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
int socket_parameters_init(){
    struct 	sockaddr_in http_server_addr;
    
    // Create TCP socket receiver
    int http_server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (http_server_fd < 0){
        perror("http_server_fd\n");
    } else printf("Create HTTP server socket successfully\n");
 
    http_server_addr.sin_family = AF_INET;                
    http_server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    http_server_addr.sin_port = htons(PORT);      

    // setsockopt() must be called before bind() so that SO_REUSEADDR can take effect
    #ifdef REUSEADDR
        int enable_val = 1;
        if (!setsockopt(http_server_fd, SOL_SOCKET, SO_REUSEADDR, &enable_val, sizeof(enable_val))){
            printf("Set socket to reuse address successfully\n");
        } else printf("Unable to set socket to reuse address\n");
    #endif

    //Bind to the local address
    if (bind(http_server_fd, (struct sockaddr *) &http_server_addr, sizeof(http_server_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start TCP socket receiver successfully through binding\n");

    //Set up connection mode for socket sender
    if (listen(http_server_fd, MAXPENDING) < 0) exit(0);

    return http_server_fd;
}