# [API](API.md)

# Single TCP receiver, single TCP sender
## Features
1. Start a TCP sender (from [tcp_multiple_senders.c](tcp_multiple_senders.c)) when the TCP receiver (from [tcp_single_receiver.c](tcp_single_receiver.c)) is not started: TCP sender prints out ``TCP receiver hasn't been started or TCP receiver doesn't support connection``
2. [TCP receiver](epoll_for_tcp_receiver.c) starts when there is no TCP sender connected/started, TCP receiver prints out **Waiting for a TCP sender to connect ...** until a TCP sender is connected.
3. [TCP receiver](epoll_for_tcp_receiver.c) accepts only 1 TCP sender connected. When **TCP receiver** successfully accepts 1 **TCP sender** connected, **TCP receiver** won't be able to detect another **TCP sender** connected to it although that new **TCP sender** will connect to **TCP receiver** successfully.
4. When a TCP sender connects to that TCP receiver, TCP receiver then prints out that TCP sender IP address. Then if that TCP sender doesn't send anything to that TCP receiver, TCP will print out **Timeout after 5000 miliseconds**. When TCP sender sends data to TCP receiver, TCP receiver will print out: ``Message from TCP sender ID: %s``
5. TCP sender is sending data to TCP receiver properly, TCP sender is then disconnected. TCP receiver is able to detect that disconnected event, print out ``New TCP sender with fd %d connected with IP %s is disconnected``. Then TCP receiver is able to accept a new connection as **TCP sender**.
## Implementation

**TCP receiver** uses [epoll](../Physical%20layer/File%20IO/System%20call/epoll/) to monitor the file descriptor of the connected **TCP sender** so that **TCP receiver** can detect the time out event (**Timeout after 5000 miliseconds**) from **TCP sender**.

* [epoll_for_tcp_receiver.c](epoll_for_tcp_receiver.c)
* [tcp_multiple_senders.c](tcp_multiple_senders.c)

# Single TCP receiver for multiple TCP senders

## Features

1. Start a TCP sender (from [tcp_multiple_senders.c](tcp_multiple_senders.c)) when the **TCP receiver** (from [tcp_single_receiver.c](tcp_single_receiver.c)) is not started: TCP sender prints out ``TCP receiver hasn't been started or TCP receiver doesn't support connection``
2. **TCP receiver** starts when there is no TCP sender connected/started, TCP receiver prints out **Waiting for a TCP sender to connect ...** until a TCP sender is connected.
3. **TCP receiver** starts then a TCP sender connects to it, TCP receiver then prints out that TCP sender IP address. Then TCP sender sends data to TCP receiver properly.
When receving message, TCP receiver will print out: ``Message from TCP sender ID %d: %s``
5. TCP receiver is able to count how many tcp_client are connected.
6. TCP sender is sending data to TCP receiver properly, TCP sender is then disconnected. TCP receiver is able to detect that disconnected event, print out ``TCP sender with ID %d is disconnected``.
7. TCP sender is identified by ID number increased by 1. If that TCP sender is disconnected, that ID number won't be used again in tcp_single_receiver.c program when another TCP sender is connected.
8. In TCP receiver, use [signal](../../Physical%20layer/Signal/) for SIGINT memory clean up process when pressing Ctr+C to stop TCP receiver. All file descriptor of connected TCP senders are closed, all fork() process to handle those TCP senders are killed.
9. Macro ``REUSEADDR`` is used to enable/disable reusable TCP receiver feature, i.e with macro ``REUSEADDR`` disable, when TCP receiver is stopped and restart it immediately, there will be issue: **Fail to bind socket to local address**. That happens as the **TIME_WAIT** parameter value define in RFC 9293 TCP. Reference to [setsockopt()](API.md#setsockopt) for details.

## Implementation

**TCP receiver** uses [fork()](../../Physical%20layer/Process/Process%20cloning) to create a new process for a file descriptor for each ``tcp_client`` every time a new connection is established.

**TCP receiver** uses [pipe()](../../Physical%20layer/File%20IO/pipe.md) to store all file descriptor of connected **TCP senders** to close them when [SIGINT signal](../../Physical%20layer/Signal/) is triggered to stop TCP receiver.

* [tcp_multiple_senders.c](tcp_multiple_senders.c)
* [tcp_single_receiver.c](tcp_single_receiver.c)

# Single TCP sender for multiple TCP receiver

## Features

1. Start a TCP receiver (from [tcp_multiple_receivers.c](tcp_multiple_receivers.c)) when the TCP sender (from tcp_single_sender.c) is not started: TCP receiver prints out ``TCP sender hasn't been started or TCP sender doesn't support connection``
2. TCP sender starts when there is no TCP receiver connected/started, TCP sender prints out ``Waiting for a TCP receiver to connect ...`` until a TCP receiver is connected.
3. TCP sender starts then a TCP receiver connects to it, TCP sender then prints out that TCP receiver IP address. Then TCP receiver sends a string ``NRC`` as a flag to TCP sender to confirm that it's ready to receive message sent from TCP sender. If TCP sender received flag ``NRC`` successfully, it will send a responded string ``String responded to TCP receiver ID %d`` to TCP receiver.

![](https://github.com/TranPhucVinh/C/blob/master/Environment/Images/single_tcp_sender_for_multiple_tcp_receivers.png)

4. TCP sender is able to count how many TCP receivers are connected.
5. While step 3 is running properly as a responded string has been sent, TCP receiver is disconnected. TCP sender is able to detect that disconnected event, print out ``TCP receiver with ID %d is disconnected``.
6. TCP receiver is identified by ID number increased by 1. If that TCP receiver is disconnected, that ID number won't be used again in [tcp_single_sender.c](tcp_single_sender.c) program when another TCP receiver is connected.

## Implementation

* [tcp_multiple_receivers.c](tcp_multiple_receivers.c)
* [tcp_single_sender.c](tcp_single_sender.c)