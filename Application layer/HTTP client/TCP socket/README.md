# HTTP request

## Get request

Get information of a hostname, like ``example.com``, including hostname and IP address, use:
* [getaddrinfo()](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/HTTP%20client#getaddrinfo): [get_host_info_getaddrinfo.c](src/get_host_info_getaddrinfo.c)
* [gethostbyname()](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/HTTP%20client/README.md#gethostbyname) (**deprecated**): [get_host_info_gethostbyname.c](src/get_host_info_gethostbyname.c)

GET request to ``example.com``: 
* [getaddrinfo()](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/HTTP%20client#getaddrinfo): [get_data_getaddrinfo.c](src/get_data_getaddrinfo.c)
* [gethostbyname()](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/HTTP%20client/README.md#gethostbyname) (**deprecated**): [get_data_gethostbyname.c](src/get_data_gethostbyname.c)

## Send data

Send data to a [Python local HTTP server](https://github.com/TranPhucVinh/Python/blob/master/Application%20layer/HTTP/HTTP%20server/README.md#http-server): 
* [send_data_getaddrinfo_char_port.c](src/send_data_getaddrinfo_char_port.c) with port as a string char
* [send_data_getaddrinfo_int_port.c](src/send_data_getaddrinfo_char_port.c) with port as a int number
* [send_data_gethostbyname.c](src/send_data_gethostbyname.c) (**deprecated**)

Send data as querystring to a local HTTP server : [send_data_by_query_string.c](src/send_data_by_query_string.c), local HTTP server which receives this data to draw chart: [Draw chart Node.js HTTP server](https://github.com/TranPhucVinh/Node.js/tree/master/Projects/Draw%20chart)

## Detect Internet connection status

TCP client for HTTP request can be used to detect Internet connection status, simply by using ``gethostbyname()`` function

**Features**:

* If Internet is connected, print ``Internet has connected``. Test with WiFi by enabling WiFi
* If Internet isn't connected, print ``No Internet connection``. Test with WiFi by disabling WiFi

**Program**:

```c
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>

#define HOST          "thingsboard.sysats.tech"

int main(int argc, char *argv[]){
    while (1){
        struct hostent *hostinfo;
        hostinfo = gethostbyname(HOST);

        if (hostinfo == NULL) printf("No Internet connection\n");
        else printf("Internet has connected\n");
        sleep(1);
    }
	return 0;
}
```

# HTTPS request

For HTTPS request, install library ``openssl``: ``sudo apt-get install libssl-dev``

Compile: ``gcc -o http-client http-client.c -lssl``

Read return message from HTTPS server: [https-request.c](https-request.c)

Read return message from ``howsmyssl.com/a/check``: ``howmyssl_https_request.c``

**Notice**:

The return value read from ``howsmyssl.com/a/check`` is different from various reading devices like web browser, IoT devices, OS process,... as it depends on the way the HTTP client performs the HTTPS request.

This HTTPS request (without ``Connection: close``) also works:

```
GET https://www.howsmyssl.com/a/check HTTP/1.1
Host:howsmyssl.com
User-Agent: esp-idf/1.0 esp32
```
