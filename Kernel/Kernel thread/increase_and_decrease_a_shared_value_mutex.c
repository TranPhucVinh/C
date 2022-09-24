#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h> //For msleep()
#include <linux/mutex.h>

#define RANGE 	20000
#define DELAY   1000

MODULE_LICENSE("GPL");
DEFINE_MUTEX(of_mutex);
struct task_struct *kthread_1, *kthread_2;

int share_value = 0;
int t1 = 1, t2 = 2;

int thread_function(void *kernel_data) {
	mutex_lock(&of_mutex);
	int option;
    option = *(int*)kernel_data;
    int i;
    for (i = 0; i < RANGE; i++)
    {
        if (option == 1) share_value++;
        else share_value--;
    }
	mutex_unlock(&of_mutex);

	while(!kthread_should_stop()) msleep(DELAY);

	return 0;
}

int init_module(void)
{
    mutex_init(&of_mutex);
    kthread_1 = kthread_create(thread_function, (void*)&t1, "kthread_1");
	wake_up_process(kthread_1); //Start kthread_1
	// if(kthread_1 != NULL){
	// 	printk("kthread_1 was created and is running now!\n");
	// }
	// else {
	// 	printk("kthread_1 could not be created!\n");
	// 	return -1;
	// }

    kthread_2 = kthread_create(thread_function, (void*)&t2, "kthread_2");
	wake_up_process(kthread_2); //Start kthread_2
	// if(kthread_2 != NULL){
	// 	printk("kthread_2 was created and is running now!\n");
	// }
	// else {
	// 	printk("kthread_2 could not be created!\n");
	// 	return -1;
	// }
    
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
    printk("share_value %d\n", share_value);
    kthread_stop(kthread_1);
	kthread_stop(kthread_2);
}