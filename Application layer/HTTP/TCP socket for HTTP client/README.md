### Example

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