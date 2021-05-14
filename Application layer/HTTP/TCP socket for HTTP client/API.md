### ``sys/socket.h``

Library **sys/socket.h** only includes in Unix computer, for similar TCP socket on Windows, use ``Winsock 2``, the library that need to be installed.

### socket()

Create new socket

```c
int socket(int protocolFamily, int  type, int protocol)
```

* **protocolFamily**: 

    ``AF_INET`` (``Address Family Internet``): IPv4 protocol (same as ``PF_INET``)

    ``AF_INET6``: IPv6 protocol (same as ``PF_INET6``)

    ``PF_INET`` stands for ``Protocol Family Internet``

* **type**: type of socket, ``SOCK_STREAM``: TCP, ``SOCK_DGRAM``: UDP
* **protocol**: Protocol used, with ``protocolFamily = PF_INET``, use ``IPPROTO_TCP`` for ``TCP`` and ``IPPROTO_UDP`` for ``UDP``

```c
int sockfd = socket(domain, type, protocol)
```

**Return**: ``sockfd`` is a file descriptor

### connect()

Connect to socket with specific address.

```c
int connect(int sockfd, struct sockaddr *addr, unsigned int addrLength) 
```

*  **sockfd**: created ``sockfd`` from function ``socket()``.
*  **addr**: server address wished to connect.
*  **addrLength**: length of Server address (byte). 4 byte for IPV4, 16 byte for IPV6.

### send() and recv()

```c
int send(int sockfd, const void *msg, unsigned int len, int flag) 
```
```c
int recv(int sockfd, void *buff, unsigned int len, int flag)
```

*  **sockfd**: created ``sockfd`` from function ``socket()``.
* ***msg**, ***buff**: pointer to ``sent`` or ``receive`` data array.
* **len**: maximum length of data array (in byte) each time ``sent`` or ``receive``.
* **flag**: set ``sent`` or ``receive`` mode. If set to ``0``, ``recv()`` is generally equivalent to ``read()``.

``send()`` and  ``recv()`` return the number of byte sent or received, return ``-1`` if there is an error.

### read() and write()

```c
ssize_t read(int sockfd, void *buf, ssize_t N);
```

Read ``N`` bytes of ``sockfd`` into the memory ``buf``

```c
ssize_t write(int sockfd, const void *buf, ssize_t N);
```

Write ``N`` bytes from ``buf`` to the ``sockfd``

**Note**: If a zero-length datagram is pending, ``read()`` and ``recv()`` with a flags argument of zero provide different behavior.  In this circumstance, ``read()`` has no effect (the datagram remains pending), while ``recv()`` consumes the pending datagram.

### listen()

Listen for connections on a socket

```c
int listen(int sockfd, int backlog);
```

``backlog``: defines the maximum length to which the queue of pending connections for ``sockfd`` may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of ``ECONNREFUSED`` or, if the underlying protocol supports retransmission, the request may be ignored so that a later reattempt at connection succeeds.

### close()

Close a socket.

```c
int close(int sockfd)
```

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

## Other libraries

``netinet/in.h``: Internet Protocol family
