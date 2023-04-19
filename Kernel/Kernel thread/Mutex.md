# Mutex for character device

To make a [character device](../Kernel/Character%20device) to be able to be opened by only 1 userspace process, use kernel ``mutex``

Add mutex to [character_device_operations.c](../Kernel/Character%20device/Character%20device%20operations/Basic%20operations/character_device_operations.c):

```c
// Other parts of the programs are identical to character_device_operations.c
#include <linux/mutex.h>

DEFINE_MUTEX(mutex);

int dev_open(struct inode *inodep, struct file *filep)
{
	// When opening device and fail to lock the mutex 
	// as another process is opening this file, return -EBUSY error
	if(!mutex_trylock(&mutex)){
		printk("%s is being used by another userspace process\n", DEVICE_NAME);
		return -EBUSY;
	} else printk("open\n");
	return 0;
}

int dev_close(struct inode *inodep, struct file *filep)
{
	mutex_unlock(&mutex);
	printk("close\n");
	return 0;
}
```

Userspace program: [user_space_2_way_communications.c](https://github.com/TranPhucVinh/C/blob/master/Kernel/Character%20device/Character%20device%20operations/Basic%20operations/user_space_2_way_communications.c)

**Result**:
Build user_space_2_way_communications.c into 2 process a1.out and a2.out. Running a1.out will read and write value to the character device as usual. While a1.out is still running, run a2.out, the result will be ``Fail to open /dev/fops_character_device``. Character device log will be ``fops_character_device is being used by another userspace process``.
# Mutex for kernel thread race condition

Use mutex to solve the race condition issue: [One thread function handler to increase and decrease a shared value](https://github.com/TranPhucVinh/C/blob/master/Kernel/Kernel%20thread/Race%20condition.md#one-thread-function-handler-to-increase-and-decrease-a-shared-value): [increase_and_decrease_a_shared_value_mutex.c](https://github.com/TranPhucVinh/C/blob/master/Kernel/Kernel%20thread/increase_and_decrease_a_shared_value_mutex.c)
