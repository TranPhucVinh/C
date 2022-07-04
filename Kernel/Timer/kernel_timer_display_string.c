/*
	Kernel module runs in 5.13.0-51-generic
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

#define DELAY 		1
#define NO_USE_FLAG	0

MODULE_LICENSE("GPL");

int 	index = 0;
struct 	timer_list kernel_timer;

void timer_callback(struct timer_list* tl){
	printk(KERN_INFO "Timer callback; index = %d\n", index);
	index += 1;

	// Modify kernel timer expire time again to run it permanently
	mod_timer(&kernel_timer, jiffies + DELAY * HZ);
}

int init_module(void)
{
	printk(KERN_INFO "Hello, World !\n");
	timer_setup(&kernel_timer, timer_callback, NO_USE_FLAG);

	kernel_timer.expires = jiffies + DELAY * HZ; //Delay at DELAY seconds for the 1st time

	add_timer(&kernel_timer);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");

	/*
		Must call del_timer() in cleanup_module() for
		running rmmod to remove the module.

		If there is no del_timer() inside cleanup_module(), running rmmod
		will cause the OS to freeze/crash
	*/
	del_timer(&kernel_timer);
}