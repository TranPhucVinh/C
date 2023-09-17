#include <stdio.h>          
#include <sys/socket.h>     /* for socket(), connect()*/
#include <stdlib.h>         /* for atoi() and exit() */
#include <string.h>         /* for memset() */
#include <unistd.h>         /* for close() */
#include <fcntl.h>          /* for open() */
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>      /* for inet_ntop() */
#include <pthread.h>

#include <vector>
#include <algorithm> // find()

#define REUSEADDR
#define MAXPENDING 	5
#define BUFFSIZE 	256
#define MAXEVENTS   1       // Maximum numbers of connected HTTP clients to handle/monitor
#define PORT 		8000

#define ELEMENT_NUMBERS 1

#define TIMEOUT     5000    // miliseconds

char        *read_file(const char *file_name);
int         socket_parameters_init();
void 		*http_client_thread_handler(void *ptr);

std::vector<int>    http_client_fd_list;

const char *httpd_hdr_str = "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n";

typedef struct _http_client_struct {
	char ip_str[30]; 
	int http_client_fd;
} http_client_struct;

int main(){
    struct 		        sockaddr_in http_client_addr;
    socklen_t 	        http_client_length;
    
    int                 http_server_fd, http_client_fd;

    http_client_length = sizeof(http_client_addr);//Get address size of sender
    http_server_fd = socket_parameters_init();

    printf("Waiting for a HTTP client to connect ...\n");
    while (1){
		if ((http_client_fd = accept(http_server_fd, (struct sockaddr *) &http_client_addr, &http_client_length)) > 0){
			char                ip_str[30];
            inet_ntop(AF_INET, &(http_client_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            http_client_fd_list.push_back(http_client_fd);
            printf("New HTTP client with fd %d connected with IP %s, %ld TCP senders have connected now\n", http_client_fd, ip_str, http_client_fd_list.size());

			pthread_t http_client_thread;

			http_client_struct *http_client_obj = (http_client_struct *)malloc(sizeof(http_client_struct));
			http_client_obj->http_client_fd = http_client_fd;
			strcpy(http_client_obj->ip_str, ip_str);

			pthread_create(&http_client_thread, NULL, http_client_thread_handler, http_client_obj);
		}
	}
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

char *read_file(const char *file_name){
    long file_size;
    FILE *fp;
	fp = fopen(file_name, "r");
	if (fp){
		fseek(fp, 0L, SEEK_END);//Set file position from index 0 to the end of file
		file_size = ftell(fp);//Then get the file size
		fseek(fp, 0L, SEEK_SET);//Return file position back to the beginning

		char *buffer;
		buffer = (char *) malloc(file_size + 1);
		bzero(buffer, file_size + 1);
		fread(buffer, file_size, ELEMENT_NUMBERS, fp);
        fclose(fp);
        return buffer;
	} else {
        printf("Unable to open file %s\n", file_name);
        return NULL;
    }
}

void *http_client_thread_handler(void *ptr){
	http_client_struct *http_client_obj;
	http_client_obj = (http_client_struct*)ptr;

	int http_client_fd;
	char req_buf[BUFFSIZE];// Buffer for HTTP request from HTTP client
	bzero(req_buf, BUFFSIZE);//Delete buffer

	http_client_fd = http_client_obj->http_client_fd;
	//putting while(1) will block another newly connected HTTP client as a new thread
	while(1){
		int bytes_received = read(http_client_fd, req_buf, BUFFSIZE);
		if (bytes_received > 0) {
			printf("New HTTP client with socket fd %d\n", http_client_fd);
			char* method = strtok(req_buf, " ");
			char* uri    = strtok(NULL, " ");

			if(!strcmp(method, "GET")){
				if(!strcmp(uri, "/")){
					int fd = open("index.html", O_RDONLY);
					if (fd > 0){
						close(fd);//Only open this file to check for its existence
						char *html = read_file("index.html");

						//HTTP response buffer size
						int rsp_buf_sz = strlen(html) + strlen(httpd_hdr_str) + strlen("200 OK") + strlen("text/html") + strlen("\r\n");

						char *res_buf = (char*) malloc(rsp_buf_sz + 1);
						bzero(res_buf, rsp_buf_sz);//Delete buffer

						snprintf(res_buf, rsp_buf_sz, httpd_hdr_str, "200 OK", "text/html", rsp_buf_sz);
						strcat(res_buf, "\r\n");
						strcat(res_buf, html);
						write(http_client_fd, res_buf, strlen(res_buf));
						free(res_buf);
						free(html);
						// printf("%s\n", res_buf);
					} else {
						char res_buf[100];
						char no_file[] = "There is no index.html file";
						snprintf(res_buf, sizeof(res_buf), httpd_hdr_str, "200 OK", "text/html", sizeof(no_file));
						strcat(res_buf, "\r\n");
						strcat(res_buf, no_file);
						// printf("%s\n", res_buf);
						write(http_client_fd, res_buf, sizeof(res_buf));
					}
				} else if (!strcmp(uri, "/favicon.ico")){// URL favicon.ico is always requested by the web browser
					printf("Simply return HTTP/1.1 200 for /favicon.ico\n");
					int rsp_buf_sz = strlen(httpd_hdr_str) + strlen("200 OK") + strlen("text/html") + strlen("\r\n");
					char *res_buf = (char*) malloc(rsp_buf_sz + 1);
					bzero(res_buf, rsp_buf_sz);//Delete buffer

					snprintf(res_buf, rsp_buf_sz, httpd_hdr_str, "200 OK", "text/html", rsp_buf_sz);
					strcat(res_buf, "\r\n");
					write(http_client_fd, res_buf, strlen(res_buf));
					free(res_buf);
				}
				else {
					char no_uri[50];
					char res_buf[100] = {0};
					int sz = sprintf(no_uri, "Not found %s", uri);
					snprintf(res_buf, sizeof(res_buf), httpd_hdr_str, "200 OK", "text/html", sz);
					strcat(res_buf, "\r\n");
					strcat(res_buf, no_uri);
					write(http_client_fd, res_buf, sizeof(res_buf));
					printf("%s\n", no_uri);
				}
			} else {
				printf("Unhandle METHOD: %s\n", method);
			}
		} else {
			auto pos = find(http_client_fd_list.begin(), http_client_fd_list.end(), http_client_fd);
			if(pos != http_client_fd_list.end()){
				http_client_fd_list.erase(pos);
			}
			printf("HTTP client with fd %d and IP %s is disconnected\n", http_client_fd, http_client_obj->ip_str);
			printf("Totally %ld HTTP clients are connected now\n", http_client_fd_list.size());
			close(http_client_fd); 
			free(http_client_obj);
			break;
		}
	}
	return NULL;
}