#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/sendfile.h>

#define BUFFSIZE    45000
#define PORT        8888
#define MAX_PENDING 5

const char *httpd_hdr_str = "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n";
char rsp_buffer[BUFFSIZE];

int main()
{
    int server_fd;
    struct sockaddr_in server, client;
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        printf("Init connection socket failed\n");
        close(server_fd);
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Error in binding connection\n");
        close(server_fd);
        exit(1);
    }

    printf("Finish setting up\n");
    unsigned int size = sizeof(server);
    listen(server_fd, MAX_PENDING);
    int client_fd;

    while(1){
        client_fd = accept(server_fd, (struct sockaddr*)&client, &size);
        if(client_fd == -1){
            printf("Connection attemp failed\n");
            continue;
        }
        printf("Requested\n");

        // client process
        if(!fork()){
            close(server_fd);

            char* buffer = malloc(BUFFSIZE);
            char* read_buffer = malloc(BUFFSIZE);
            char* temper_buffer = malloc(BUFFSIZE);
            char* temper_read = malloc(BUFFSIZE);
            bzero(buffer, BUFFSIZE);
            bzero(read_buffer, BUFFSIZE);
            bzero(temper_buffer, BUFFSIZE);
            bzero(temper_read, BUFFSIZE);

            read(client_fd, read_buffer, BUFFSIZE);
            memcpy(temper_read, read_buffer, BUFFSIZE);
            
            // printf("%s\n", read_buffer);
            FILE* fp;
            char* method = strtok(read_buffer, " ");
            char* uri    = strtok(NULL, " ");
            char* prot   = strtok(NULL, "\r\n");

            // printf("%s\n", buffer);
            if(!strcmp(method, "GET")){
                if(!strcmp(uri, "/")){
                    fp = fopen("index.html", "rb");
                    int sz = fread(temper_buffer, 1, BUFFSIZE, fp);
                    int sz1 = snprintf(buffer, BUFFSIZE, httpd_hdr_str, "200 OK", "text/html", sz);
                    strcat(buffer, "\r\n");
                    strcat(buffer, temper_buffer);
                    write(client_fd, buffer, strlen(buffer));
                } 
			} else {
                // handle http error at here
			}
            free(buffer);
            free(read_buffer);
            free(temper_buffer);
            free(temper_read);
            fclose(fp);
            // printf("METHOD:%s//\n", method);
            // printf("URI:%s//\n", uri);
            // printf("PROT:%s//\n", prot);
            close(client_fd);
            exit(0);
        }
        //server process
        close(client_fd);
    }
    return 0;
}