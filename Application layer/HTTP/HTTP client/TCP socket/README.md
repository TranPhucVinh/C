# Examples

## HTTP request

* GET request ``example.com``: ``get_data.c``

``get_data.c`` can be performed with dynamic allocation:

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

* Send data to a local HTTP server: ``send_data.c``

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