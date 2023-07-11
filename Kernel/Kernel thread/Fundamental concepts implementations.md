# Create a single kernel thread and send an int number as argument to it

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h> //For msleep()

#define DELAY   1000

MODULE_LICENSE("GPL");

struct task_struct *kthread_1;
int kernel_data = 123;

int thread_function(void *kernel_data) {
    printk("Kernel data %d\n", *(int*)kernel_data);

	/*
		Must have kthread_should_stop() for safe memory when running rmmod
		and msleep() for infinite sleep.
	*/
	while(!kthread_should_stop()){
		msleep(DELAY);
	}
	return 0;
}

int init_module(void)
{
    kthread_1 = kthread_create(thread_function, &kernel_data, "kthread_1");
	if(kthread_1 != NULL){
		wake_up_process(kthread_1); //Start kthread_1
		printk("kthread_1 was created and is running now!\n");
	}
	else {
		printk("kthread_1 could not be created!\n");
		return -1;
	}
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
    kthread_stop(kthread_1);
}
```

**Note**: If the infinite loop is ``while(!kthread_should_stop());`` then the OS will be hung immediately right after running ``insmod``.

# Print out a string every 1 second in a kernel thread

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h> //For msleep()

#define DELAY   1000

MODULE_LICENSE("GPL");

struct task_struct *kthread_1;

int thread_function(void *kernel_data) {
    int index = 0;

	while(!kthread_should_stop()){
        printk("Hello, World !; index %d\n", index);
        index += 1;
        msleep(DELAY);
	}
	return 0;
}

int init_module(void)
{
    kthread_1 = kthread_create(thread_function, NULL, "kthread_1");
	if(kthread_1 != NULL){
		wake_up_process(kthread_1); //Start kthread_1
		printk("kthread_1 was created and is running now!\n");
	}
	else {
		printk("kthread_1 could not be created!\n");
		return -1;
	}
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
    kthread_stop(kthread_1);
}
```
