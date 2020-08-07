## sockaddr, in_addr, sockaddr_in

Library ``arpa/inet.h``

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

**sockaddr** and **sockaddr_in** are used to set up address parameter for **client** and **server**.

* **sin_family**, **sa_family**: protocolFamily
* **sin_port**: port of socket
* **sin_addr**: connect address
* **sin_zero**: not used, set value 0

### htons

```c
u_short htons(
  u_short hostshort
);
```

The **htons** function converts a ``u_short`` from host to TCP/IP network byte order (which is big-endian).

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