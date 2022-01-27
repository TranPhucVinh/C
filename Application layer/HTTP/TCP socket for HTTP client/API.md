## sys/socket.h

### listen()

Listen for connections on a socket

```c
int listen(int sockfd, int backlog);
```

``backlog``: defines the maximum length to which the queue of pending connections for ``sockfd`` may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of ``ECONNREFUSED`` or, if the underlying protocol supports retransmission, the request may be ignored so that a later reattempt at connection succeeds.

### accept()

```c
int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
```
Accept a connection on a socket

### send() and recv()

```c
int send(int sockfd, const void *msg, unsigned int len, int flag) 
```
```c
int recv(int sockfd, void *buff, unsigned int len, int flag)
```

* ``sockfd``: created ``sockfd`` from function ``socket()``.
* ``*msg``, ``*buff``: pointer to ``sent`` or ``receive`` data array.
* ``len``: maximum length of data array (in byte) each time ``sent`` or ``receive``.
* ``flag``: set ``sent`` or ``receive`` mode. If set to ``0``, ``recv()`` is generally equivalent to ``read()``.

``send()`` and  ``recv()`` return the number of byte sent or received, return ``-1`` if there is an error.

**Note**: If a zero-length datagram is pending, ``read()`` and ``recv()`` with a flags argument of zero provide different behavior.  In this circumstance, ``read()`` has no effect (the datagram remains pending), while ``recv()`` consumes the pending datagram.

Sending and receiving process can be executed with

``send()`` in [tcp-client.c](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/HTTP/TCP%20socket%20for%20HTTP%20client/tcp-client.c)

```c
if (send(sockfd, buffer, strlen(buffer)-1, 0) < 0) 
    error("ERROR writing to socket");
else printf("finish writing: %s", buffer);    
```

``read()`` in [tcp-server.c](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/HTTP/TCP%20socket%20for%20HTTP%20client/tcp-server.c)

```c
n = read(client_fd, buffer, 1024);
printf("%s\n", buffer);
```

## netdb.h

### socket()

Create new socket

```c
int socket(int protocolFamily, int  type, int protocol)
```

* ``protocolFamily``: 

    ``AF_INET`` (``Address Family Internet``): IPv4 protocol (same as ``PF_INET``)

    ``PF_INET`` stands for ``Protocol Family Internet``

    ``AF_INET6``: IPv6 protocol (same as ``PF_INET6``)

* ``type``: type of socket, ``SOCK_STREAM``: TCP, ``SOCK_DGRAM``: UDP
* ``protocol``: Protocol used, with ``protocolFamily = PF_INET``, use ``IPPROTO_TCP`` for ``TCP`` and ``IPPROTO_UDP`` for ``UDP``

**Return**: A file descriptor for the created socket

### connect()

Connect to socket with specific address.

```c
int connect(int sockfd, struct sockaddr *addr, unsigned int addrLength) 
```

*  ``sockfd``: created ``sockfd`` from function ``socket()``.
*  ``addr``: server address wished to connect.
*  ``addrLength``: length of Server address (byte). 4 byte for IPV4, 16 byte for IPV6.

### shutdown()

Shut down all or part of the connection open on ``sockfd``

```c
int shutdown(int sockfd, int how)
```

``how`` determines what to shut down:

* ``SHUT_RD``: No more receptions
* ``SHUT_WR``: No more transmissions
* ``SHUT_RDWR``: No more receptions or transmissions

**Return**: ``0`` success,`` -1`` errors

### Other functions

```c
struct hostent *hp;
```

```c
herror();
```

```c
gethostbyname()
```

### htons

```c
u_short htons(
  u_short hostshort
);
```

The ``htons`` function converts a ``u_short`` from host to TCP/IP network byte order (which is big-endian).

### hostent

```c
struct hostent {
    char  *h_name;            /* official name of host */
    char **h_aliases;         /* alias list */
    int    h_addrtype;        /* host address type */
    int    h_length;          /* length of address */
    char **h_addr_list;       /* list of addresses */
}
```

## arpa/inet.h

### sockaddr, in_addr, sockaddr_in

```c
struct sockaddr { 
    unsigned short sa_family;
    char  sa_data[14] ; /* Family-specific address information */
}; 

struct in_addr {
    unsigned long s_addr;
};

struct sockaddr_in{
    unsigned short sin_family;
    unsigned short sin_port; /* Address port (16 bits) */
    struct in_addr sin_addr; /* Internet address (32 bits) */
    char    sin_zero[8]; /* Not used, must be zero */
};
```

``sockaddr`` and ``sockaddr_in`` are used to set up address parameter for client and server.

* ``sin_family``, ``sa_family``: protocolFamily
* ``sin_port``: port of socket
* ``sin_addr``: connect address
* ``sin_zero``: not used, set value 0

## Other libraries

``netinet/in.h``: Internet Protocol family
