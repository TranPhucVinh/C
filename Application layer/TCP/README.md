TCP sockets program can be used to inter process communication.

# API

[API.md](API.md)

# Single TCP receiver for multiple TCP senders

### Feature

1. Start a TCP sender (from tcp_multiple_senders.c) when the TCP receiver (from tcp_single_receiver.c) is not started: TCP sender prints out ``TCP receiver hasn't been started or TCP receiver doesn't support connection``
2. TCP receiver starts when there is no TCP sender connected/started, TCP receiver print out ``Waiting for a TCP sender to connect ...`` until a TCP sender is connected.
3. TCP receiver starts then a TCP sender connects to it, TCP receiver then prints out that TCP sender IP address. Then TCP sender sends data to TCP receiver properly.
When receving message, TCP receiver will print out: ``Message from TCP sender ID %d: %s``
5. Able to count how many tcp_client are connected.
6. TCP sender is sending data to TCP receiver properly, TCP sender is then disconnected. TCP receiver is able to detect that disconnected event, print out ``TCP sender  with ID %d is disconnected``.
7. TCP sender is identified by ID number increased by 1. If that TCP sender is disconnected, that ID number won't be used again in tcp_single_receiver.c program when another TCP sender is connected.

### Implementation

Use [fork()](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/Process/Process%20cloning) to create a new process for a file descriptor for each ``tcp_client`` every time a new connection is established:

* [tcp_multiple_senders.c](tcp_multiple_senders.c)
* [tcp_single_receiver.c](tcp_single_receiver.c)
