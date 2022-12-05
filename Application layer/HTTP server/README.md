# HTTP server built from TCP server

**Feature**:

Handle GET request:
* Return a text/plain string for route ``/``
* Return HTML as the content of file ``index.html`` for route ``/getfile``. If file ``index.html`` not existed, return text/plain ``File index.html not existed``.
* For routing with unhandled route, return ``Not found %s``

To simplify the program, those features are not supported:
* Count total numbers of connected TCP client (handled by [mmap()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Virtual%20memory.md#mmap) like in [tcp_single_sender.c](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/TCP/tcp_single_sender.c))
* Detect disconnected event (handled by fork() like in [tcp_single_sender.c](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/TCP/tcp_single_sender.c))

**Note**: Stopping then running the program multiple times result in this error

```
Create TCP server socket successfully
Fail to bind socket to local address
```

**Program**: [simple_http_server.c](simple_http_server.c)
