HTTP client implemented by

* [TCP socket API](TCP%20socket)
* [libcurl](libcurl)

# API

**netdb.h** defines the following API:

## getaddrinfo()

```c
int getaddrinfo(const char *restrict node, const char *restrict service, const struct addrinfo *restrict hints, struct addrinfo **restrict res);
```

## gethostbyname()

``gethostbyname()``, which is now **deprecated**, will get information of a given host, especially its hostname and IP address:
 
```c
struct hostent *gethostbyname(const char *name);
```

```c
struct hostent {
    char  *h_name;            /* official name of host */
    char **h_aliases;         /* A zero-terminated array of alternate names for the host */
    int    h_addrtype;        /* host address type */
    int    h_length;          /* length of address */
    char **h_addr_list;       /* A zero-terminated array of addresses from name server*/
}
```

```c
#include <netdb.h>
extern int h_errno;
```

``h_errno`` refers to the host error.

The ``herror()`` function prints the error message associated with the current value of h_errno on stderr.
## struct addrinfo 
```c
struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    socklen_t        ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};
```

## htons

```c
u_short htons(u_short hostshort);
```

The ``htons`` function converts a ``u_short`` from host to TCP/IP network byte order (which is big-endian).
