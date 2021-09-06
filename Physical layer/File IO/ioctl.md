```c
#include <sys/ioctl.h>
int ioctl(int fd , int request , ... /* argp */);
```

``request`` are defined in ``ioctls.h``

## Examples

**Example 1**: Get size of the terminal running the current C program

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

Get size of the terminal running the current C program when changing its size by mouse, check ``Example 2: Working with SIGWINCH signal`` in ``Signal/Examples.md``.