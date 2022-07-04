/*
	Kernel module runs in 5.13.0-51-generic
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/slab.h> //for kmalloc()

#define DELAY 		1
#define NO_USE_FLAG	0

MODULE_LICENSE("GPL");

int 	index = 0;
// struct 	timer_list kernel_timer;

struct timer_data {
	struct timer_list timer;
	int arg;
};

typedef struct timer_data timer_data;
timer_data *td;

void timer_callback(struct timer_list* tl){
	td = from_timer(td, tl, timer);
	printk(KERN_INFO "Timer callback; index = %d; arg %d\n", index, td->arg);
	index += 1;

	// Modify kernel timer expire time again to run it permanently
	mod_timer(&(td->timer), jiffies + DELAY * HZ);
}

int init_module(void)
{
	printk(KERN_INFO "Hello, World !\n");

    td = (timer_data*) kmalloc(sizeof(timer_data), GFP_KERNEL);

	// td->timer = kernel_timer;
	td->arg = 123;
	
	timer_setup(&(td->timer), timer_callback, NO_USE_FLAG);

	(td->timer).expires = jiffies + DELAY * HZ; //Delay at DELAY seconds for the 1st time

	add_timer(&(td->timer));
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
	del_timer(&(td->timer));
}