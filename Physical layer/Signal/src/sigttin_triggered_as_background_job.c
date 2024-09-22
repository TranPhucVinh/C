#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>   

#define TERMINAL "/dev/pts/0"

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
    if (signal_number == SIGTTIN) {
        int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal SIGTTIN is caught\n");
    	write(STDOUT_FILENO, displayed_string, sz); 
    }
}

int main() {
    signal(SIGTTIN, signal_handler);
	int fd = open(TERMINAL, O_RDWR);
	if (fd > 0){
        printf("open %s successfully\n", TERMINAL);
        char buffer[10];
        bzero(buffer, sizeof(buffer));//Empty the previously entered buffer
        read(fd, buffer, sizeof(buffer));
	} else printf("Unable to open\n");
}
