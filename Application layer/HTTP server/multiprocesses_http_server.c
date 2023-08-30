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

#define REUSEADDR
#define MAXPENDING 	5
#define BUFFSIZE 	256
#define PORT 		8000

#define ELEMENT_NUMBERS 1

//Macro for mmap() setup
#define PAGE_SIZE   4048
#define NO_FD       -1  //No file descriptor used for shared memory
#define BASE_ADDR   0   //No specific base address to set in shared memory

char        *read_file(const char *file_name);
int         socket_parameters_init();
void        sigint_handler(int signal_number);

int         http_client_fd_pipe[2];
int         *total_conn_http_client;//Total numbers of connected HTTP client
int         http_client_id = 0;
const char  *httpd_hdr_str = "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n";

int main(){
    struct 		        sockaddr_in http_client_addr;
    socklen_t 	        http_client_length;
    
    int                 http_server_fd, http_client_fd;

    http_client_length = sizeof(http_client_addr);//Get address size of sender
    http_server_fd = socket_parameters_init();

    printf("Waiting for a HTTP client to connect ...\n");
    while (1){
        // wait for a new HTTP client to connect, return new socket for that HTTP client
        if ((http_client_fd = accept(http_server_fd, (struct sockaddr *) &http_client_addr, &http_client_length)) > 0){
            char                ip_str[30];
            inet_ntop(AF_INET, &(http_client_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            *total_conn_http_client += 1;
            http_client_id += 1;
            printf("New HTTP client with fd %d connected with IP %s, %d TCP senders have connected now\n", http_client_fd, ip_str, *total_conn_http_client);

            write(http_client_fd_pipe[1], &http_client_fd, sizeof(int));

            int pid = fork();
            if (!pid) {
                char req_buf[BUFFSIZE];// Buffer for HTTP request from HTTP client
                bzero(req_buf, BUFFSIZE);//Delete buffer

                printf("Connected HTTP client has ID %d\n", http_client_id); 
                while (1){
                    int bytes_received = read(http_client_fd, req_buf, BUFFSIZE);
                    if (bytes_received > 0) {
                        printf("Message from HTTP client with socket fd %d: %s", http_client_fd, req_buf);
                        char* method = strtok(req_buf, " ");
                        char* uri    = strtok(NULL, " ");

                        if(!strcmp(method, "GET")){
                            if(!strcmp(uri, "/")){
                                int fd = open("index.html", O_RDONLY);
                                if (fd > 0){
                                    close(fd);//Only open this file to check for its existence
                                    char *html = read_file("index.html");

                                    //HTTP response buffer size
                                    int rsp_buf_sz = strlen(html) + sizeof(httpd_hdr_str) + sizeof("200 OK") + sizeof("text/html") + sizeof("\r\n");

                                    char *res_buf = (char*) malloc(rsp_buf_sz);
                                    bzero(res_buf, rsp_buf_sz);//Delete buffer

                                    snprintf(res_buf, rsp_buf_sz, httpd_hdr_str, "200 OK", "text/html", rsp_buf_sz);
                                    strcat(res_buf, "\r\n");
                                    strcat(res_buf, html);
                                    write(http_client_fd, res_buf, rsp_buf_sz);
                                    printf("%s\n", res_buf);
                                } else {
                                    char res_buf[100];
                                    char no_file[] = "There is no index.html file";
                                    snprintf(res_buf, BUFFSIZE, httpd_hdr_str, "200 OK", "text/html", sizeof(no_file));
                                    strcat(res_buf, "\r\n");
                                    strcat(res_buf, no_file);
                                    printf("%s\n", res_buf);
                                    write(http_client_fd, res_buf, BUFFSIZE);
                                }
                            }
                            else {
                                char no_uri[50];
                                char res_buf[100];
                                int sz = sprintf(no_uri, "Not found %s", uri);
                                snprintf(res_buf, BUFFSIZE, httpd_hdr_str, "200 OK", "text/html", sz);
                                strcat(res_buf, "\r\n");
                                strcat(res_buf, no_uri);
                                write(http_client_fd, res_buf, BUFFSIZE);
                            }
                        }
                    }
                    else {
                        printf("HTTP client sender with ID %d is disconnected\n", http_client_id);
                        *total_conn_http_client -= 1;
                        printf("%d TCP senders have connected now\n", *total_conn_http_client);
                        close(http_server_fd); 
                        kill(getpid(), SIGKILL); 
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
    
    //Must use MAP_ANONYMOUS as no file descriptor used for shared memory (macro NO_FD)
    total_conn_http_client = (int *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, NO_FD, BASE_ADDR);
    *total_conn_http_client = 0;

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

/*
    SIGINT signal handler will clean up memory when pressing CTR+C (SIGINT) by:
    * close all senders fd
    * kill all processes (child and parent) in the process group
*/
void sigint_handler(int signal_number){
    close(http_client_fd_pipe[1]);

    int *http_client_fd_arr = (int*) malloc(*total_conn_http_client * sizeof(int));  

    read(http_client_fd_pipe[0], http_client_fd_arr, *total_conn_http_client * sizeof(int));
    close(http_client_fd_pipe[0]);

    // kill() pid=0 to kill all processes (child and parent) in the process group
    kill(0, SIGKILL);

    for (int i = 0; i < *total_conn_http_client; i++){
        printf("http_client_fd_arr[%d] %d\n", i, http_client_fd_arr[i]);
        close(http_client_fd_arr[i]);
    }
    exit(0);
}

char *read_file(const char *file_name){
    long file_size;
    FILE *fp;
	fp = fopen(file_name, "r");
	if (fp){
		fseek(fp, 0L, SEEK_END);//Set file position from index 0 to the end of file
		file_size = ftell(fp);//Then get the file size
		fseek(fp, 0L, SEEK_SET);//Return file position back to the beginning

		char *buffer;
		buffer = (char *) malloc(file_size);
		bzero(buffer, file_size);
		fread(buffer, file_size, ELEMENT_NUMBERS, fp);
        return buffer;
	} else {
        printf("Unable to open file %s\n", file_name);
        return NULL;
    }
}
