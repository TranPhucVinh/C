# listen()

Listen for TCP connections on a TCP socket

```c
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```

``backlog``: defines the maximum length to which the queue of pending connections for ``sockfd`` may grow. If a connection request arrives when the queue is full, the client may receive an error with an indication of ``ECONNREFUSED`` or, if the underlying protocol supports retransmission, the request may be ignored so that a later reattempt at connection succeeds.

In [tcp_single_receiver.c](tcp_single_receiver.c) program, with ``MAXPENDING`` is set to ``5`` for ``backlog`` parameters, when initiating more than 5 new TCP client ([tcp_multiple_senders.c](tcp_multiple_senders.c)) connection at the same time, i.e 6 connections, and even start sending data to TCP server at the same time, ``ECONNREFUSED`` error don't return as expected theoretically. That might happen as those 6 TCP client connection might not actually coming at TCP server at the same time and the queue can still pack them properly.

As defined, ``listen()`` is only used for TCP, not UDP. When calling ``listen()`` for UDP socket error **95** (**EOPNOTSUPP**) **Operation not supported**.

# accept()

```c
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
```
Accept a connection on a socket. If no pending connections are present on the queue, and the socket is not marked as nonblocking, ``accept()`` blocks the caller until a connection is present.

**Return**:
* A file descriptor for the accepted socket (a nonnegative integer), when success
* ``-1`` on error
# setsockopt()

```c
#include <sys/socket.h>
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```
Set options on sockets. On success, ``0`` is returned. On error, ``-1`` is returned.
* ``level``: The level at which the option resides. For options at the **socket level**, set to ``SOL_SOCKET``
* ``optname``: Option name depended on the ``level`` set before
* ``optlen``: For socket level option, ``optlen`` must be nonzero to enable a boolean option, or zero if the option is to be disabled. With ``level=SOL_SOCKET``, ``enable_val=NULL`` and ``optlen=0`` ``setsockopt()`` return ``-1`` (fail)

RFC 9293 defines:

* **MSL** (**Maximum Segment Lifetime**), the time a TCP segment can exist in the internetwork system. Arbitrarily defined to be 2 minutes. 
* **TIME_WAIT = MSL*2**

So by default (i.e without ``setsockopt()`` setup), after stopping a TCP server, like [tcp_single_receiver.c](tcp_single_receiver.c) which includes ``bind()`` to bind socket to current IP address, then restart it immediately, ``bind()`` function will fail, with error log for that [tcp_single_receiver.c](tcp_single_receiver.c) program is **Fail to bind socket to local address**

That happen as the time interval between 2 stop and restart time is less than **TIME_WAIT**. User has to wait for that time interval to be greater than **TIME_WAIT** to restart the server.

To start that server immediately right after stopping it, ``setsockopt()`` must be used with ``optname=SO_REUSEADDR`` (fully implemented in [tcp_single_receiver.c](tcp_single_receiver.c)):

```c
setsockopt(receiver_fd, SOL_SOCKET, SO_REUSEADDR, &enable_val, sizeof(enable_val));
```
# socket()
Create new socket
```c
#include <sys/socket.h>
int socket(int protocolFamily, int  type, int protocol)
```

* ``protocolFamily``: 
    * ``AF_INET`` (``Address Family Internet``): IPv4 protocol (same as ``PF_INET``)
    * ``PF_INET`` stands for ``Protocol Family Internet``
    * ``AF_INET6``: IPv6 protocol (same as ``PF_INET6``)
```C
// socket.h define
#define AF_INET		PF_INET
```
* ``type``: type of socket, ``SOCK_STREAM``: TCP, ``SOCK_DGRAM``: UDP
* ``protocol``: Protocol used, with ``protocolFamily = PF_INET``, use ``IPPROTO_TCP`` for ``TCP`` and ``IPPROTO_UDP`` for ``UDP``

**Return**: A file descriptor for the created socket

# connect()

Connect to socket with specific address

```c
#include <sys/socket.h>
int connect(int sockfd, struct sockaddr *addr, unsigned int addrLength) 
```

*  ``sockfd``: created ``sockfd`` from function ``socket()``.
*  ``addr``: server address wished to connect.
*  ``addrLength``: length of Server address (byte). 4 byte for IPV4, 16 byte for IPV6.
# shutdown()

Shut down all or part of the connection open on ``sockfd``

```c
#include <sys/socket.h>
int shutdown(int sockfd, int how)
```

``how`` determines what to shut down:

* ``SHUT_RD``: No more receptions
* ``SHUT_WR``: No more transmissions
* ``SHUT_RDWR``: No more receptions or transmissions

**Return**: ``0`` success,`` -1`` errors
# Send message to socket

Beside ``write()``, there are 3 more functions to send message to socket:
```c
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
```
**write()**, **send()**, and **sendto()** are all used for TCP socket (i.e connection-mode, **SOCK_STREAM**)

The only difference between ``send()`` and ``write()`` is the presence of flags. With a zero flags argument, **send()** is equivalent to **write()**.

For UDP socket, flag **MSG_CONFIRM** must be used 
