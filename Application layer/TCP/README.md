TCP sockets program can be used to inter process communication.

# API

[API.md](API.md)

# Examples

### Feature

1. Start tcp_client when tcp_server is not started: tcp_client print out tcp_server not connected
Print message: ``Server hasn't been started or server doesn't support connection``
2. tcp_server starts when there is no tcp_client connected/started, tcp_server print out ``Waiting for a TCP client to connect ...`` until a tcp_client is connected.
3. tcp_server starts then a tcp_client connects to it, tcp_server then prints out that tcp_client IP address. Then tcp_client sends data to tcp_server properly.
4. Support multiple tcp_client to a tcp_server. Print out meesage: ``Message from TCP client ID %d: %s``
5. Able to count how many tcp_client are connected.

### Implementation

Use [fork()](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Process%20cloning) to create a new process for a file descriptor for each ``tcp_client`` every time a new connection is established:

* [tcp_client.c](tcp_client.c)
* [tcp_server.c](tcp_server.c)

### TBD

1. ``tcp_client`` is sending data to ``tcp_server`` properly, tcp_client then disconnected. tcp_server is able to detect that disconnected event, print out ``TCP client with IP xx has disconnected``. That tcp_client and tcp_server are then able to recover connection and transmission if that tcp_client is started again.
