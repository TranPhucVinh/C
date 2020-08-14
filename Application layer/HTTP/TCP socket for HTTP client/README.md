**Note**: All the program below only works with Unix socket, and don't work in Windows.

### Sending data between 2 TCP client

* ``tcp-client.c``
* ``tcp-server.c``

TCP client sends entered string to TCP server.

Sending and receiving process can be executed with

``send()`` in ``tcp-client.c``

```c
if (send(sockfd, buffer, strlen(buffer)-1, 0) < 0) 
    error("ERROR writing to socket");
else printf("finish writing: %s", buffer);    
```

``read()`` in ``tcp-server.c``

```c
n = read(client_fd, buffer, 1024);
printf("%s\n", buffer);
```

### HTTP request with TCP client socket

Send HTTP request from a TCP client socket to a HTTP server: ``http-client.c``

This work with all HTTP webpage and local Python HTTP server.

### HTTPS request

For HTTPS request, install library ``openssl``: ``sudo apt-get install libssl-dev``

Compile: ``gcc -o http-client http-client.c -lssl``

**Example**:

Read return message from HTTPS server: ``https-request.c``