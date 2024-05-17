# SIGIO
SIGIO is sent when a file descriptor is ready to perform input or output.

On most operating systems, terminals and sockets are the only kinds of files that can generate SIGIO; other kinds, including ordinary files, never generate SIGIO even if you ask them to.

On GNU systems SIGIO will always be generated properly if you successfully set asynchronous mode with fcntl.

SIGIO is triggered when typing into the terminal:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

void sigio_handler(int sig);
int  sigio_setup_for_stdin_fd();

int main() {
    sigio_setup_for_stdin_fd();

    printf("Waiting for input to the terminal...\n");
    while (1) {
        pause();// Suspend the current process until SIGIO is triggered by typing to STDIN_FILENO
    }

    return 0;
}

void sigio_handler(int sig) {
    char rd_buf[50], wr_buf[100];

    bzero(rd_buf, sizeof(rd_buf));
    bzero(wr_buf, sizeof(wr_buf));
    
    int bytes_read = read(STDIN_FILENO, rd_buf, sizeof(rd_buf) - 1);

    rd_buf[bytes_read] = '\0'; // Null-terminate rd_buf
    sprintf(wr_buf, "SIGIO is triggered; Entered string: %s", rd_buf);
    write(STDOUT_FILENO, wr_buf, sizeof(wr_buf) - 1);
}

int sigio_setup_for_stdin_fd() {
    struct sigaction sa;
    int flags;

    // Set up the SIGIO signal handler
    sa.sa_handler = sigio_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGIO, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Get the file descriptor flags
    if ((flags = fcntl(STDIN_FILENO, F_GETFL)) == -1) {
        perror("fcntl(F_GETFL)");
        exit(EXIT_FAILURE);
    }

    // Set the file descriptor to non-blocking mode
    if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK | O_ASYNC) == -1) {
        perror("fcntl(F_SETFL)");
        exit(EXIT_FAILURE);
    }

    // Set the process to receive SIGIO signals for the file descriptor
    if (fcntl(STDIN_FILENO, F_SETOWN, getpid()) == -1) {
        perror("fcntl(F_SETOWN)");
        exit(EXIT_FAILURE);
    }
}
```
