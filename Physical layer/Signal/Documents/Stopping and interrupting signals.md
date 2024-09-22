# SIGHUP, SIGUSR1, SIGUSR2 can stop a process without signal_handler()
An infinite running process like this can be stopped by SIGHUP, SIGUSR1, SIGUSR2
```c
int main(void)
{
	while(1)
	{
        printf("Hello, World !\n");
        sleep(1);
	}
}
```
