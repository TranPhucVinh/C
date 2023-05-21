HTTP client implemented by

* TCP socket API
* libcurl

# API

## netdb.h

### gethostbyname()

Get information of a given host
 
```c
struct hostent *gethostbyname(const char *name);
```

```c
struct hostent {
    char  *h_name;            /* official name of host */
    char **h_aliases;         /* A zero-terminated array of alternate names for the host */
    int    h_addrtype;        /* host address type */
    int    h_length;          /* length of address */
    char **h_addr_list;       /* A zero-terminated array of network addresses for the host. Host addresses are returned in network byte order*/
}
```

```c
#include <netdb.h>
extern int h_errno;
```

``h_errno`` refers to the host error.

The ``herror()`` function prints the error message associated with the current value of h_errno on stderr.

### htons

```c
u_short htons(
  u_short hostshort
);
```

The ``htons`` function converts a ``u_short`` from host to TCP/IP network byte order (which is big-endian).