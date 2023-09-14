#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

#define DEV_NAME    "DEV_NAME IRQ_1"
#define DEV_ID    	"DEV_ID" //DEV_ID must not be NULL, if using NULL for DEv_ID, request_irq() will fail

#define IRQ_1		1

MODULE_LICENSE("GPL");

int pressed_times = 0;

void workqueue_function(struct work_struct *work);

DECLARE_WORK(static_workqueue, workqueue_function);

irq_handler_t irq_1_handler(unsigned int irq, void* dev_id, struct pt_regs *regs){
	printk("Device ID %s; Keyboard interrupt occured %d\n", (char*)dev_id, pressed_times);
	pressed_times += 1;

	schedule_work(&static_workqueue);

    return (irq_handler_t) IRQ_HANDLED;
}

int init_module(void)
{
	printk(KERN_INFO "Hello, World !\n");
    if (request_irq(IRQ_1, (irq_handler_t) irq_1_handler, IRQF_SHARED, DEV_NAME, DEV_ID) != 0){
        printk("Can't request interrupt number %d\n", IRQ_1);
    } else printk("Request interrupt number %d successfully\n", IRQ_1);

	return 0;
}

void cleanup_module(void)
{
    /*
        Must have free_irq() function in cleanup (for rmmod command)
        If not having free_irq(), the interrupt still existed in /proc/interrupts after calling rmmod
    */
	free_irq(IRQ_1, DEV_ID);
	destroy_work_on_stack(&static_workqueue);
	printk(KERN_INFO "clean up module\n");
}

/* Bottom half workqueue handler */
void workqueue_function(struct work_struct *work)
{
	printk("Workqueue function is called; pressed time %d\n", pressed_times);
}