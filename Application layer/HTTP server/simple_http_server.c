#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/wait.h>

#define BUFFSIZE    1000
#define PORT        8000
#define MAX_PENDING 5
#define	FILE_NAME		"index.html"

const char *httpd_hdr_str = "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n";

int 		server_fd, client_fd;
struct 		sockaddr_in server_addr, client_addr;
socklen_t 	client_length;

void socket_parameter_init(){
    //Create TCP socket server
    if ((server_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("tcp_server\n");
    } else printf("Create TCP server socket successfully\n");
 
    server_addr.sin_family = AF_INET;                
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(PORT);      

    //Bind to the local address
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Fail to bind socket to local address\n");
        exit(0);
    }
    else printf("Start TCP socket server successfully through binding\n");

    //Set up connection mode for socket server
    if (listen(server_fd, MAX_PENDING) < 0) exit(0);

    client_length = sizeof(client_addr);//Get address size of server
   	
}

int main()
{
    socket_parameter_init();
	printf("Waiting for a TCP client to connect ...\n");

    while(1){
        if((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_length)) > 0 ){
			char* buffer = malloc(BUFFSIZE);
			char* temp_buffer = malloc(BUFFSIZE);
			bzero(buffer, BUFFSIZE);
			bzero(temp_buffer, BUFFSIZE);

			char ip_str[30];
            inet_ntop(AF_INET, &(client_addr.sin_addr.s_addr), ip_str, INET_ADDRSTRLEN);
            printf("New TCP client connected with IP %s\n", ip_str);

			int bytes_received = read(client_fd, buffer, BUFFSIZE);
			if (bytes_received > 0) {
				char* method = strtok(buffer, " ");
				char* uri    = strtok(NULL, " ");
				char* prot   = strtok(NULL, "\r\n");

				if(!strcmp(method, "GET")){
					if (!strcmp(uri, "/")){
						int sz = sprintf(temp_buffer, "Text responsed from TCP server");
						int snz = snprintf(buffer, BUFFSIZE, httpd_hdr_str, "200 OK", "text/plain", sz);
						strcat(buffer, "\r\n");
						strcat(buffer, temp_buffer);
						write(client_fd, buffer, sz+snz+2);
					} else if (!strcmp(uri, "/getfile")){
						int fd = open(FILE_NAME, O_RDONLY);
						if (fd > 0){
							int sz = read(fd, temp_buffer, BUFFSIZE);
							int snz = snprintf(buffer, BUFFSIZE, httpd_hdr_str, "200 OK", "text/html", sz);
							strcat(buffer, "\r\n");
							strcat(buffer, temp_buffer);
							write(client_fd, buffer, strlen(buffer));
							close(fd);
						} else {
							int sz = sprintf(temp_buffer, "File %s not found", FILE_NAME);
							int snz = snprintf(buffer, BUFFSIZE, httpd_hdr_str, "200 OK", "text/plain", sz);
							strcat(buffer, "\r\n");
							strcat(buffer, temp_buffer);
							write(client_fd, buffer, sz+snz+2);
						}
					} else {
						int sz = sprintf(temp_buffer, "Not found %s", uri);
						int snz = snprintf(buffer, BUFFSIZE, httpd_hdr_str, "200 OK", "text/plain", sz);
						strcat(buffer, "\r\n");
						strcat(buffer, temp_buffer);
						write(client_fd, buffer, sz+snz+2);
					}
				} 

				free(buffer);
				free(temp_buffer);
				close(client_fd);

				bzero(buffer, BUFFSIZE);         //Delete buffer
			} 			
	    }
	}
    return 0;
}
