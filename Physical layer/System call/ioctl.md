```c
#include <sys/ioctl.h>
int ioctl(int fd , int request , ... /* argp */);
```

``request`` are defined in ``ioctls.h``

Value returned on success depends on request, or ``–1`` on error.

``ioctl()`` information is divided into the following topics:
* Terminals
* Sockets
* STREAMS
* ACLs

# Get size of the terminal running the current C program

```c
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	struct winsize ws;//defined in sys/ioctl
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

	printf("rows: %d\n", ws.ws_row);
	printf("columns: %d\n", ws.ws_col);

	return (0);
}
```

Using ``ioctl()`` to get size of the terminal running the current C program when changing its size by mouse, check [SIGWINCH signal example](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Signal/Working%20with%20specific%20signal.md#sigwinch).

It is also possible to change the terminal driver’s notion of the window size by passing an initialized winsize structure in an ``ioctl()`` ``TIOCSWINSZ`` operation:

```c
struct winsize ws;//defined in sys/ioctl
ws.ws_row = 50;
ws.ws_col = 50;
ioctl(STDIN_FILENO, TIOCSWINSZ, &ws);
```

If the new values in the winsize structure differ from the terminal driver’s current notion of the terminal window size, two things happen:

* The terminal driver data structures are updated using the values supplied in the ``ws`` argument.
* A ``SIGWINCH`` signal is sent to the foreground process group of the terminal.

Note, however, that these events on their own are insufficient to change the actual dimensions of the displayed window, which are controlled by software outside the kernel (such as a window manager or a terminal emulator program).

# [Communication between userpsace process and character device by ioctl](https://github.com/TranPhucVinh/C/tree/master/Kernel/Character%20device/Character%20device%20operations/ioctl)

# [Communication between userpsace process and I2C bus device by ioctl in Raspbian with various I2C modules and sensors](https://github.com/TranPhucVinh/Raspberry-Pi-C/tree/main/Sensors%20and%20Modules#i2c)

# [Read and write RTC time of /dev/rtc](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Time/Examples.md#read-and-write-rtc-time-of-devrtc)

# [ioctl for GPIO device file](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/blob/main/Physical%20layer/GPIO/GPIO%20device%20file.md) 
