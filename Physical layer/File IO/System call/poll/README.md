# API
``poll()`` performs a similar task to [select()](select.md), it waits for one of a set of file descriptors to become ready to perform I/O

```c
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

```c
struct pollfd {
    int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
```

``nfds_t``: An unsigned integer type used for the number of file descriptors.

**Parameters**

* ``nfds``: Total number of file descriptors to monitor by ``poll()``
* ``events``: A bit mask specifying the events the application is interested in for the file descriptor ``fd``. It is an input parametr (i.e setup in program)

    * ``POLLIN``: There is data to read.
    * ``POLLOUT``: Writing is now possible

* ``revents``:  The bits returned in ``revents`` can include any of those specified in ``events``, or one of the values ``POLLERR``, ``POLLHUP``, or ``POLLNVAL``. It is an output parameter, i.e return in function ``poll()``

**Return**:  

* On success, a positive number is returned
* ``0``: Call timed out and no file descriptors were ready.
* ``-1``: Error

# poll() to monitor 1 file descriptor as the current running terminal

Read entered data from the current running terminal: [poll_for_1_terminal.c](poll_for_1_terminal.c)

**Result**

* If not entering anything to the terminal for ``TIMEOUT`` ms, print out ``Timeout after TIMEOUT miliseconds``
* If entering a string inside ``TIMEOUT`` ms, print out that entered string by the chunk of ``BUFF_SIZE``, i.e

Entering ``1234567890`` (10 character), print out ``Entered string: 1234567890``

Entering ``1234567890123`` (More than 10 characters), print out: 

``Entered string: 1234567890``

``Entered string: 123``

# poll() to monitor multiple file descriptors as 2 current running terminals

Read entered data from the 2 current running terminals:

* Current running program (a.out) on 1st terminal /dev/pts/1
* 2nd terminal is /dev/pts/2

**Program**: [poll_for_multiple_terminals.c](poll_for_multiple_terminals.c)

**Result**

* If not entering anything to 2 terminals for ``TIMEOUT`` ms, print out ``Timeout after TIMEOUT miliseconds``
* If entering a string inside ``TIMEOUT`` ms on the 1st terminal ``/dev/pts/1`` (running ``a.out``), print out that entered string by the chunk of ``BUFF_SIZE``, i.e

Entering ``1234567890`` (10 character): Print out ``String from terminal 1: 1234567890``

Entering ``1234567890123`` (More than 10 characters): Print out 

``String from terminal 1: 1234567890``

``String from terminal 1: 123``

* If entering a string inside ``TIMEOUT`` ms on the 2nd terminal ``/dev/pts/2``, print out every character inside that entered string, i.e

Entering ``1234567890`` (10 character): Print out: 

* ``String from terminal 2: 1``
* ``String from terminal 2: 2``

... Print out every single chracter inside ``buffer[BUFF_SIZE]``

* ``String from terminal 2: 9``
* ``String from terminal 2: 0``
# poll() with character device

Response any poll event from a character device to a userspace process opening it. Check [poll in Character device operations](../../../../Kernel/Character%20device/Character%20device%20operations/Poll/README.md#poll-handling-in-character-device)