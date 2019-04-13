# API

### socket()

Create new socket

```c
int socket(int protocolFamily, int  type, int protocol)
```

* **protocolFamily**: ``AF_INET`` (IPv4 protocol), ``AF_INET6`` (IPv6 protocol), ``PF_INET``: Protocol Family Internet, AF_INET: Address Family Internet.
* **type**: type of socket, ``SOCK_STREAM``: used for TCP, ``SOCK_DGRAM``: used for UDP.
* **protocol**: Protocol used, with protocolFamily = PF_INET, use ``IPPROTO_TCP`` for **TCP** and ``IPPROTO_UDP`` for **UDP**

### close()

Close a socket.

```c
int close(int socket)
```

**C-programming**

sys/types.h - data types

## sys/socket.h

sys/socket.h - Internet Protocol family

socket():  create an endpoint for communication

ref: [sys/socket.h](http://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html)

## netinet/in.h

netinet/in.h - Internet Protocol family

