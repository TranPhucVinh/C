# arpa/inet.h

## inet_ntoa()
```c
char *inet_ntoa(struct in_addr in);
```
Convert [struct in_addr](#sockaddr-inaddr-sockaddrin) into IPv4 string.

For an implementation to parse IPv4 address from [struct in_addr](#sockaddr-inaddr-sockaddrin), check [gethostbyname()]() [example to get the hostname information, including its IP address](../Application%20layer/HTTP%20client/TCP%20socket/get_host_information.c).

## inet_ntop()

```c
#include <arpa/inet.h>
const char *inet_ntop(int af, const void *restrict src, char *restrict dst, socklen_t size);
```

``inet_ntop``: convert IPv4 and IPv6 addresses from binary to text form

## sockaddr, in_addr, sockaddr_in

```c
struct sockaddr { 
    unsigned short sa_family;
    char  sa_data[14] ; /* Family-specific address information */
}; 

struct in_addr {
    unsigned long s_addr; /* address in network byte order */
};

struct sockaddr_in{
    unsigned	short sin_family;
    unsigned	short sin_port; /* Address port (16 bits) */
    struct		in_addr sin_addr; /* Internet address (32 bits) */
    char    	sin_zero[8]; /* Not used, must be zero */
};
```

``sockaddr`` and ``sockaddr_in`` are used to set up IPv4 address parameter for client and server.

* ``sin_family``, ``sa_family``: protocolFamily
* ``sin_port``: port of socket
* ``sin_addr``: IP address in byte order. When ``INADDR_ANY`` is specified in the bind call, the socket will be bound to all local interfaces. For example in [Raspbian Busybox when the loopback interface isn't booted up automatically](), ``INADDR_ANY`` will bind to the Ethernet interface ``eth0`` instead. With ``INADDR_ANY`` specified, then ``localhost``, ``0.0.0.0`` and ``127.0.0.1`` will all be available.
* ``sin_zero``: not used, set value 0

To bind to the IP address of the current device, e.g ``192.168.1.4``, use inet_addr:
```c
http_server_addr.sin_addr.s_addr = inet_addr("192.168.1.4");
```
For an implementation to parse IPv4 address from struct sockaddr_in, check [gethostbyname()]() [example to get the hostname information, including its IP address](../Application%20layer/HTTP%20client/TCP%20socket/get_host_information.c).

## sockaddr_un
**sockaddr_un** is used to setup Unix socket:
```c
struct sockaddr_un {
    sa_family_t sun_family;     // AF_UNIX
    char sun_path[108];         // Pathname
};
```
# Other libraries

``netinet/in.h``: Internet Protocol family
