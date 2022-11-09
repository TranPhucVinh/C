#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>   
#include <fcntl.h>

#define DEV_NAME "/dev/fops_character_device"

void signal_handler(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main(){ 
	signal(SIGUSR1, signal_handler);
	int fd = open(DEV_NAME, O_RDWR); //READ ONLY
	if(fd < 0) {
		printf("Fail to open %s\n", DEV_NAME);
		close(fd);
		return 1;
	}
	else {
		while(1);
	}
}