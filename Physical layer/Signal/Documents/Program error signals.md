# SIGFPE
Report SIGFPE when storing the divided-by-0 result into a variable:

```c
void div_by_zero(int signal_number){
	char displayed_string[50];
	bzero(displayed_string, 50);
	int sz = snprintf(displayed_string, sizeof(displayed_string), "Signal %d is caught, divided by 0\n", signal_number);
	write(STDOUT_FILENO, displayed_string, sz); 
}

int main(){ 
	signal(SIGFPE, div_by_zero);
	sleep(5);
	int a = 5/0;
	return 0;
}
```
**Result**

```c
Signal 8 is caught, divided by 0
Signal 8 is caught, divided by 0
.... // Run forever
```
**Must**: The divided-by-0 result must be stored into a variable to trigger **SIGFPE**. If simply call ``5/0``, **SIGFPE** won't be triggered.
# SIGBUS
When mapping memory with mmap() for an unnamed semaphore with the wrong length, SIGBUS is triggered. Program: [trigger_sigbus_by_mmap.c](../src/trigger_sigbus_by_mmap.c)

Check the [sem_init implementation for process race condition: Two processes increase the value of a POSIX shared memory region](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Process/Race%20condition/2_processes_increase_a_posix_shared_mem_value_sem_init.c) for the correct way of mapping memory for unnamed semaphore.