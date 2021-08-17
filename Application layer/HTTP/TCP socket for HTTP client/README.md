### Sending data between only 2 TCP client

* ``tcp-client.c``
* ``tcp-server.c``

TCP client sends the entered string to TCP server. TCP server can't receive the message from one more TCP client.

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

GET request to a HTTP server like ``example.com`` or local HTTP server: ``get_data.c``

## HTTPS request

For HTTPS request, install library ``openssl``: ``sudo apt-get install libssl-dev``

Compile: ``gcc -o http-client http-client.c -lssl``

### Examples

Read return message from HTTPS server: ``https-request.c``

Read return message from ``howsmyssl.com/a/check``: ``howmyssl_https_request.c``

**Notice**: The return value read from ``howsmyssl.com/a/check` is different from reading them directly from web browser, due to security reason.