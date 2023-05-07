# Terminal operations

Inside the ``while()`` loop, read entered value from terminal and print out:

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	while(1){
		char buffer[10];
        bzero(buffer, sizeof(buffer));//Empty the previously entered buffer
		read(STDIN_FILENO, buffer, sizeof(buffer));
		write(STDOUT_FILENO, buffer, sizeof(buffer));
	}
}
```

**Note**: Using ``read()`` with other ``stdout`` functions like ``puts()``, ``printf()``, ... results in garbage value printing and other ``stdout`` error.

Read entered data from the current running terminal (``/dev/tty``)

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

const char filePath[] = "/dev/tty";
char bufferRead[20];

int fileDescription;
void delaySeconds(long seconds);

int main(){
   fileDescription = open(filePath, O_RDONLY); //READ ONLY
   while(1){
	   bzero(bufferRead, sizeof(bufferRead));
      if(fileDescription < 0) return 1;
      else {
         read(fileDescription, bufferRead, sizeof(bufferRead));
         printf("%s", bufferRead);
      }
   }
    return 0;
}
```

# USB ports operations

Read data from USB port (``/dev/ttyUSB0``, ``/dev/ttyACM0``,...) with baudrate 115200 as default USB port baudrate

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

const char filePath[] = "/dev/ttyACM0";
char bufferRead[20];

int fd;

int main(){
    fd = open(filePath, O_RDONLY); //READ ONLY
    while(1){
        if(fd < 0) return 1;
        else {
            read(fd, bufferRead, sizeof(bufferRead));
            printf("%s", bufferRead);
        }
        memset(bufferRead, 0, sizeof(bufferRead));
        sleep(1);
    }
    return 0;
}
```

For reading from USB port with other baudrate value like 4800, 9600,... use ``termios.h`` functions:

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <termios.h>
#include <errno.h> 

const char filePath[] = "/dev/ttyUSB0";
char bufferRead[20];

int serial_port;
struct termios tty;

int main(){
    serial_port = open(filePath, O_RDONLY); //READ ONLY
    // Read in existing settings, and handle any error
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    while(1){
        if(serial_port < 0) return 1;
        else {
            read(serial_port, bufferRead, sizeof(bufferRead));
            printf("%s", bufferRead);
        }
        memset(bufferRead, 0, sizeof(bufferRead));
        sleep(1);
    }
   
    return 0;
}
```

For other baurdate value like 4800, use ``B4800``:

```C
cfsetispeed(&tty, B4800);
cfsetospeed(&tty, B4800);
```

# Read coordinate of a mouse cursor

**Note**: This program only work with pluggable mouse and don't work with hardware built-in touchpad as touchpad is not treated as mouse.

To view the mouse id, use command: ``ll /dev/input/by-path`` or ``ll /dev/input/by-id``

Must run the program below with ``sudo`` to read the ``/dev/input/event*``: [read_coordinate_of_mouse_cursor.c](read_coordinate_of_mouse_cursor.c)

**Result**: Result will be like this
```
x=42 y=16
x=145 y=16
x=691 y=16
```
