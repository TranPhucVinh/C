# HTTP request

## Get request

GET request ``example.com``: [get_data.c](get_data.c)

[get_data.c](get_data.c) can be performed with dynamic allocation:

```c
int main(int argc, char *argv[]){
	int fd;
	char *buffer;

    while (1){
        buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
        fd = socket_connect(HOST, PORT); 
        char *http_request = form_http_request();

        write(fd, http_request, strlen(http_request)); // write(fd, char[]*, len);  
        bzero(buffer, BUFFER_SIZE);
        
        while(read(fd, buffer, BUFFER_SIZE) != 0){
            fprintf(stderr, "%s", buffer);
            bzero(buffer, BUFFER_SIZE);
        }

        shutdown(fd, SHUT_RDWR); 
        close(fd); 
        free(buffer);

        sleep(1);
    }
	return 0;
}
```

## Send data

Send data to a local HTTP server: [send_data.c](send_data.c)

Local HTTP server used for testing: [Python HTTP server](https://github.com/TranPhucVinh/Python/blob/master/Application%20layer/HTTP/HTTP%20server/README.md#http-server)

## Detect Internet connection status

TCP client for HTTP request can be used to detect Internet connection status, simply by using ``gethostbyname()`` function

**Features**:

* If Internet is connected, print ``Internet has connected``. Test with WiFi by enabling WiFi
* If Internet isn't connected, print ``No Internet connection``. Test with WiFi by disabling WiFi

**Program**:

```c
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>

#define HOST          "thingsboard.sysats.tech"

int main(int argc, char *argv[]){
    while (1){
        struct hostent *hostinfo;
        hostinfo = gethostbyname(HOST);

        if (hostinfo == NULL) printf("No Internet connection\n");
        else printf("Internet has connected\n");
        sleep(1);
    }
	return 0;
}
```

## HTTPS request

For HTTPS request, install library ``openssl``: ``sudo apt-get install libssl-dev``

Compile: ``gcc -o http-client http-client.c -lssl``

Read return message from HTTPS server: ``https-request.c``

Read return message from ``howsmyssl.com/a/check``: ``howmyssl_https_request.c``

**Notice**:

The return value read from ``howsmyssl.com/a/check`` is different from various reading devices like web browser, IoT devices, OS process,... as it depends on the way the HTTP client performs the HTTPS request.

This HTTPS request (without ``Connection: close``) also works:

```
GET https://www.howsmyssl.com/a/check HTTP/1.1
Host:howsmyssl.com
User-Agent: esp-idf/1.0 esp32
```
