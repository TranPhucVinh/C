#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> //for open()
#include <unistd.h>
#include <sys/ioctl.h>

#define CHAR_DEV     "/dev/fops_character_device"
#define DISABLE_IRQ          _IO('d', 0)
#define ENABLE_IRQ           _IO('e', 0)

char disable_irq[] = "disable_irq";
char enable_irq[] = "enable_irq";

int main(int argc, char *argv[]) {
	int fd = open(CHAR_DEV, O_RDWR);
	if (fd > 0){
		switch (argv[1][0]){
			case 'd':
			{
				if (ioctl(fd, DISABLE_IRQ, disable_irq) == -1) {
					printf("DISABLE_IRQ fail\n");
				} else {
					printf("Perform DISABLE_IRQ successfully\n");
				}
				break;
			}

			case 'e':
			{
				if (ioctl(fd, ENABLE_IRQ, enable_irq) == -1) {
					printf("ENABLE_IRQ fail\n");
				} else {
					printf("Perform ENABLE_IRQ successfully\n");
				}
				break;
			}
			default:
			{
				printf("Invalid argument to enable/disable interrupt for %s\n", CHAR_DEV);
				break;
			}
		}
	} else printf("Unable to open %s\n", CHAR_DEV);

    close(fd);
}	
