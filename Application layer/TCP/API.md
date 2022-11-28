## sys/socket.h

### listen()

Listen for connections on a socket

```c
int listen(int sockfd, int backlog);
```

``backlog``: defines the maximum length to which the queue of pending connections for ``sockfd`` may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of ``ECONNREFUSED`` or, if the underlying protocol supports retransmission, the request may be ignored so that a later reattempt at connection succeeds.

In [tcp_server.c](tcp_server.c) program, with ``MAXPENDING`` is set to ``5`` for ``backlog`` parameters, when initiating more than 5 new TCP client ([tcp_client.c](tcp_client.c)) connection at the same time, i.e 6 connections, and even start sending data to TCP server at the same time, ``ECONNREFUSED`` error don't return as expected theoretically. That might happen as those 6 TCP client connection might not actually coming at TCP server at the same time and the queue can still pack them properly.

### accept()

```c
int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
```
Accept a connection on a socket. If no pending connections are present on the queue, and the socket is not marked as nonblocking, ``accept()`` blocks the caller until a connection is present.

## netdb.h

### gethostbyname()

Look up an IP address from a domain name
 
```c
struct hostent *gethostbyname(const char *name);
```

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

### inet_ntop()

```c
#include <arpa/inet.h>
const char *inet_ntop(int af, const void *restrict src, char *restrict dst, socklen_t size);
```

``inet_ntop``: convert IPv4 and IPv6 addresses from binary to text form

### sockaddr, in_addr, sockaddr_in

```c
struct sockaddr { 
    unsigned short sa_family;
    char  sa_data[14] ; /* Family-specific address information */
}; 

struct in_addr {
    unsigned long s_addr; /* address in network byte order */
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
* ``sin_addr``: connect address. When ``INADDR_ANY`` is specified in the bind call, the socket will be bound to all local interfaces.
* ``sin_zero``: not used, set value 0

## Other libraries

``netinet/in.h``: Internet Protocol family
