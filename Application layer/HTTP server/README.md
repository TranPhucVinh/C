# Simple HTTP server built on TCP API

**Feature**:

Handle GET request:
* Return a text/plain string for route ``/``
* Return HTML as the content of file ``index.html`` for route ``/getfile``. If file ``index.html`` not existed, return text/plain ``File index.html not existed``.
* For routing with unhandled route, return ``Not found %s``

As a simple HTTP server, those features are not supported:
* Count total numbers of connected TCP client (handled by [mmap()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Virtual%20memory.md#mmap) like in [tcp_single_sender.c](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/TCP/tcp_single_sender.c))
* Detect disconnected event (handled by fork() like in [tcp_single_sender.c](https://github.com/TranPhucVinh/C/blob/master/Application%20layer/TCP/tcp_single_sender.c))

**Program**: [simple_http_server.c](simple_http_server.c)

# HTTP server for multiple HTTP client, monitored by [epoll](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/System%20call/epoll)
**Features**

* Return HTML as the content of file ``index.html`` for route ``/``. If file ``index.html`` not existed, return text/plain ``File index.html not existed``.
* For routing with unhandled route, return ``Not found %s``
* [HTTP server](epoll_for_http_server.c) starts when there is no HTTP client connected and sending HTTP request, HTTP receiver prints out **Waiting for a TCP sender to connect ...** until a HTTP client is connected.
* When there is no new HTTP client connected to TCP receiver or the connected HTTP client doesn't send anything to HTTP server, HTTP server will print out **Timeout after 5000 miliseconds**.
* **TCP receiver** is able to count how many **TCP senders** are connected and able to detect the disconnected event, print out ``TCP sender with fd %d and IP %s is disconnected``.

**Program**: [epoll_for_http_server.c](epoll_for_http_server.c)
