# Examples

## HTTP request

* GET request to a HTTP server like ``example.com`` or local HTTP server: ``get_data.c``
* Send data to a local HTTP server: ``send_data.c``

## HTTPS request

For HTTPS request, install library ``openssl``: ``sudo apt-get install libssl-dev``

Compile: ``gcc -o http-client http-client.c -lssl``

Read return message from HTTPS server: ``https-request.c``

Read return message from ``howsmyssl.com/a/check``: ``howmyssl_https_request.c``

**Notice**:

The return value read from ``howsmyssl.com/a/check`` is different from various reading devices like web browser, IoT devices, OS process,... as it depends on the way the HTTP client performs the HTTPS request.

This HTTPS request (without ``Connection: close``) also works:

```
GET https://www.howsmyssl.com/a/check HTTP/1.1
Host:howsmyssl.com
User-Agent: esp-idf/1.0 esp32
```