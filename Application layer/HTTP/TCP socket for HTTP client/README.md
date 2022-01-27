# API

[API.md](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/HTTP/TCP%20socket%20for%20HTTP%20client/API.md)

# Examples

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

* GET request to a HTTP server like ``example.com`` or local HTTP server: ``get_data.c``
* Send data to a local HTTP server: ``send_data.c``

## HTTPS request

For HTTPS request, install library ``openssl``: ``sudo apt-get install libssl-dev``

Compile: ``gcc -o http-client http-client.c -lssl``

### Examples

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