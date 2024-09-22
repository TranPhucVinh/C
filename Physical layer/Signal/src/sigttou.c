#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>   
#include <termios.h>
#include <errno.h> 

#define TERMINAL "/dev/pts/1"

struct termios tty;

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
    if (signal_number == SIGTTOU) {
        int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal SIGTTOU is caught\n");
    	write(STDOUT_FILENO, displayed_string, sz); 
    }
}

int main() {
    signal(SIGTTOU, signal_handler);
	int fd = open(TERMINAL, O_RDWR);
	if (fd > 0){
        printf("open %s successfully\n", TERMINAL);

		// Read in existing settings, and handle any error
		if(tcgetattr(fd, &tty) != 0) {
			printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		tty.c_iflag |= TOSTOP;

		// Save tty settings, also checking for error
		if (tcsetattr(fd, TCSANOW, &tty) != 0) {
			printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		char hw[] = "Hello, World !";
        write(fd, hw, sizeof(hw));
	} else printf("Unable to open\n");
}
