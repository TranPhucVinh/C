# [API](API.md)
* [Socket parameters setup](API%20socket%20parameters%20setup.md)
* [Socket operations](API%20socket%20operations.md):
  * listen(), accept(), setsockopt(), socket(), connect(), shutdown()
  * Send message to socket: write(), send(), sendto()
# A TCP sender sends string to a TCP receiver

## Features
1. Start a TCP sender (from [tcp_sgl_sndr_sgl_rx.c](src/tcp_sgl_sndr_sgl_rx.c)) when the TCP receiver (from [tcp_sgl_rx_sgl_sndr.c](src/tcp_sgl_rx_sgl_sndr.c)) is not started: TCP sender prints out ``TCP receiver hasn't been started or TCP receiver doesn't support connection``
2. [TCP receiver](src/tcp_sgl_rx_sgl_sndr.c) starts when there is no TCP sender connected/started, TCP receiver prints out **Waiting for a TCP sender to connect ...** until a TCP sender is connected.
3. **TCP receiver** starts then a TCP sender connects to it, TCP receiver then prints out that TCP sender IP address. Then TCP sender sends data to TCP receiver properly.
4. TCP sender is sending data to TCP receiver properly, TCP sender is then disconnected. TCP receiver is able to detect that disconnected event, print out ``TCP sender has disconnected. Stop TCP receiver, too``. TCP receiver then stops

## Program
* TCP receiver (TCP single receiver for a single TCP sender): [tcp_sgl_rx_sgl_sndr.c](src/tcp_sgl_rx_sgl_sndr.c)
* TCP sender (TCP single sender for a single TCP receiver): [tcp_sgl_sndr_sgl_rx.c](src/tcp_sgl_sndr_sgl_rx.c)

# Single TCP receiver for multiple TCP senders, handled by [epoll](../Physical%20layer/File%20IO/System%20call/epoll/)
## Features
1. Start a TCP sender (from [tcp_multiple_senders.c](src/tcp_multiple_senders.c)) when the TCP receiver (from [epoll_for_tcp_receiver.c](src/epoll_for_tcp_receiver.c)) is not started: TCP sender prints out ``TCP receiver hasn't been started or TCP receiver doesn't support connection``
2. [TCP receiver](src/epoll_for_tcp_receiver.c) starts when there is no TCP sender connected/started, TCP receiver prints out **Waiting for a TCP sender to connect ...** until a TCP sender is connected.
3. When there is no new TCP sender connected to TCP receiver or the connected TCP receiver doesn't send anything to TCP sender, TCP receiver will print out **Timeout after 5000 miliseconds**.
4. **TCP receiver** starts then a TCP sender connects to it, TCP receiver then prints out that TCP sender IP address. Then TCP sender sends data to TCP receiver properly.
When receving message, TCP receiver will print out: ``Message from TCP sender with fd %d: %s``
5. **TCP receiver** is able to **count how many TCP senders are connected**.
6. TCP sender is sending data to TCP receiver properly, TCP sender is then disconnected. TCP receiver is able to detect that disconnected event, print out ``TCP sender with fd %d and IP %s is disconnected``.

## Implementation

**TCP receiver** uses [epoll](https://github.com/TranPhucVinh/C/tree/master/Physical%20layer/File%20IO/System%20call/epoll) with EPOLLIN event type.

For TCP socket, EPOLLIN event type is triggered in the TCP receiver when:
* A new TCP sender connects successfully to that TCP receiver
* A connected TCP sender write data to that TCP receiver

**Program**:
* [epoll_tcp_sgl_rx_multi_sndr.c](src/epoll_tcp_sgl_rx_multi_sndr.c)
* [tcp_multi_sndr_epoll_sgl_rx.c](src/tcp_multi_sndr_epoll_sgl_rx.c)

# Single TCP receiver for multiple TCP senders, handled by fork()

## Features

1. Start a TCP sender (from [tcp_multiple_senders.c](src/tcp_multiple_senders.c)) when the **TCP receiver** (from [tcp_single_receiver.c](src/tcp_single_receiver.c)) is not started: TCP sender prints out ``TCP receiver hasn't been started or TCP receiver doesn't support connection``
2. **TCP receiver** starts when there is no TCP sender connected/started, TCP receiver prints out **Waiting for a TCP sender to connect ...** until a TCP sender is connected.
3. **TCP receiver** starts then a TCP sender connects to it, TCP receiver then prints out that TCP sender IP address. Then TCP sender sends data to TCP receiver properly.
When receving message, TCP receiver will print out: ``Message from TCP sender ID %d: %s``
5. **TCP receiver** is able to count how many **TCP senders** are connected.
6. TCP sender is sending data to TCP receiver properly, TCP sender is then disconnected. TCP receiver is able to detect that disconnected event, print out ``TCP sender with ID %d is disconnected``.
7. TCP sender is identified by ID number increased by 1. If that TCP sender is disconnected, that ID number won't be used again in tcp_single_receiver.c program when another TCP sender is connected.
8. In TCP receiver, use [signal](../../Physical%20layer/Signal/) for SIGINT memory clean up process when pressing Ctr+C to stop TCP receiver. All file descriptor of connected TCP senders are closed, all fork() process to handle those TCP senders are killed.
9. Macro ``REUSEADDR`` is used to enable/disable reusable TCP receiver feature, i.e with macro ``REUSEADDR`` disable, when TCP receiver is stopped and restart it immediately, there will be issue: **Fail to bind socket to local address**. That happens as the **TIME_WAIT** parameter value define in RFC 9293 TCP. Reference to [setsockopt()](API.md#setsockopt) for details.

## Implementation

**TCP receiver** uses [fork()](../../Physical%20layer/Process/Process%20cloning) to create a new process for a file descriptor for each ``tcp_client`` every time a new connection is established.

**TCP receiver** uses [pipe()](../../Physical%20layer/File%20IO/pipe.md) to store all file descriptor of connected **TCP senders** to close them when [SIGINT signal](../../Physical%20layer/Signal/) is triggered to stop TCP receiver.

* [tcp_multiple_senders.c](tcp_multiple_senders.c)
* [tcp_single_receiver.c](tcp_single_receiver.c)

# [Single TCP receiver for multiple TCP senders, handled by multithread](https://github.com/TranPhucVinh/Cplusplus/tree/master/Transport%20layer#single-tcp-receiver-for-multiple-tcp-senders-handled-by-multithread)
**Note**: This implementation has a special feature: **TCP receiver** only **accepts a specific number of connected TCP senders**, defined by **MAX_CONNECTIONS** in **TCP receiver source code**.
# Single TCP sender for multiple TCP receiver, handled by fork()

## Features

1. Start a TCP receiver (from [tcp_multiple_receivers.c](src/tcp_multiple_receivers.c)) when the TCP sender (from tcp_single_sender.c) is not started: TCP receiver prints out ``TCP sender hasn't been started or TCP sender doesn't support connection``
2. TCP sender starts when there is no TCP receiver connected/started, TCP sender prints out ``Waiting for a TCP receiver to connect ...`` until a TCP receiver is connected.
3. TCP sender starts then a TCP receiver connects to it, TCP sender then prints out that TCP receiver IP address. Then TCP receiver sends a string **NRC** (stands for **New Receiver Connected**) as a flag to TCP sender to confirm that it's ready to receive message sent from TCP sender. If TCP sender received flag ``NRC`` successfully, it will send a responded string ``String responded to TCP receiver ID %d`` to TCP receiver.

![](https://github.com/TranPhucVinh/C/blob/master/Environment/Images/single_tcp_sender_for_multiple_tcp_receivers.png)

4. TCP sender is able to count how many TCP receivers are connected.
5. While step 3 is running properly as a responded string has been sent, TCP receiver is disconnected. TCP sender is able to detect that disconnected event, print out ``TCP receiver with ID %d is disconnected``.
6. TCP receiver is identified by ID number increased by 1. If that TCP receiver is disconnected, that ID number won't be used again in [tcp_single_sender.c](src/tcp_single_sender.c) program when another TCP receiver is connected.

## Implementation

* [tcp_multiple_receivers.c](src/tcp_multiple_receivers.c)
* [tcp_single_sender.c](src/tcp_single_sender.c)

# A UDP sender sends string to a UDP receiver
* Based on the UDP mechanism, a [UDP sender](src/udp_sgl_sndr_sgl_rx.c) can start normally without the need of an existing UDP receiver. UDP sender doesn't need to connect to the targeted UDP receiver (by connect()) before sending message.
* Simply start the [UDP receiver](src/udp_sgl_rx_sgl_sndr.c) then both **UDP sender** and **receiver** can start exchanging message.
* For programming, as using **sendto()** (in [UDP sender](src/udp_sgl_sndr_sgl_rx.c)) which requires **sockaddr_in**  as parameter, a socket param init function, like [socket_parameter_init(char *host, int port)]() in **TCP**, can't be used. It's better to handle this [encapsulation](https://github.com/TranPhucVinh/Cplusplus/blob/master/Object-oriented%20programming/README.md#encapsulation) in UDP by using OOP.

**Note**: A UDP server can't detect how many UDP clients are connected to it. Users might need to design the message sent from UDP client to UDP server with specific types of ID so that the UDP server can detect the clients to count.

**Program**: 
* **Feature**: UDP sender reads the typed-in message from stdin then sends that message to any UDP receivers listening to it.
* UDP receiver (UDP single receiver for a single UDP sender): [udp_sgl_rx_sgl_sndr.c](src/udp_sgl_rx_sgl_sndr.c)
* UDP sender (UDP single sender for a single UDP receiver): [udp_sgl_sndr_sgl_rx.c](src/udp_sgl_sndr_sgl_rx.c)
# A multithread UDP receiver reads message sent from a UDP sender
All features are like [A UDP sender sends string to a UDP receiver](), except UDP receiver has multiple thread to reads the message.

* UDP receiver: [udp_multithread_receiver.c](src/udp_multithread_receiver.cpp)
* UDP sender: [udp_sgl_sndr_sgl_rx.c](src/udp_sgl_sndr_sgl_rx.c)
