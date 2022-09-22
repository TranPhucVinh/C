# One thread function handler to increase a shared value

No race condition happens when using one thread function handler to increase a shared value

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h> //For msleep()

#define RANGE 	9000000
#define DELAY   1000

MODULE_LICENSE("GPL");

struct task_struct *kthread_1, *kthread_2;

int share_value;

int thread_function(void *kernel_data) {
	int i;
	for (i = 0; i < RANGE; i++)	share_value++;
	while(!kthread_should_stop()){
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

    kthread_2 = kthread_create(thread_function, NULL, "kthread_2");
	if(kthread_2 != NULL){
		wake_up_process(kthread_2); //Start kthread_2
		printk("kthread_2 was created and is running now!\n");
	}
	else {
		printk("kthread_2 could not be created!\n");
		return -1;
	}
    
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
    printk("share_value %d\n", share_value);
    kthread_stop(kthread_1);
	kthread_stop(kthread_2);
}
```

**Result**: When ``rmmod``: ``share_value 18000000``

# Accessing a shared variable between 2 thread function handlers

No race condition happens when accessing a shared variable between 2 thread function handlers:

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h> //For msleep()

#define DELAY   1000

MODULE_LICENSE("GPL");

struct task_struct *kthread_1, *kthread_2;

char displayed_string[30];

int func_thread_1(void *ptr){
	printk("Thread 1\n");
	sprintf(displayed_string, "%s", "Hello, World !");	
	while(!kthread_should_stop()){
		msleep(DELAY);
	}
	return 0;
}

int func_thread_2(void *ptr){
	printk("%s\n", displayed_string);
	printk("Thread 2\n");
	while(!kthread_should_stop()){
		msleep(DELAY);
	}
	return 0;
}

int init_module(void)
{
    kthread_1 = kthread_create(func_thread_1, NULL, "kthread_1");
	if(kthread_1 != NULL){
		wake_up_process(kthread_1); //Start kthread_1
	}
	else {
		printk("kthread_1 could not be created!\n");
		return -1;
	}

    kthread_2 = kthread_create(func_thread_2, NULL, "kthread_2");
	if(kthread_2 != NULL){
		wake_up_process(kthread_2); //Start kthread_2
	}
	else {
		printk("kthread_2 could not be created!\n");
		return -1;
	}
    
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
    kthread_stop(kthread_1);
	kthread_stop(kthread_2);
}
```

**Result**

```
[927998.694234] Thread 1
[927998.694245] Hello, World !
[927998.694246] Thread 2
```