#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

#define DEV_NAME    "DEV_NAME IRQ_1"
#define DEV_ID    	"DEV_ID" //DEV_ID must not be NULL

#define IRQ_1		1

MODULE_LICENSE("GPL");

int pressed_times = 0;

irq_handler_t irq_1_handler(unsigned int irq, void* dev_id, struct pt_regs *regs){
	printk("Device ID %s; Keyboard interrupt occured %d\n", (char*)dev_id, pressed_times);
	pressed_times += 1;
    return (irq_handler_t) IRQ_HANDLED;
}

int init_module(void)
{
	printk(KERN_INFO "Hello, World !\n");

    /*
        Notes:
        1. Use OR flag IRQF_SHARED|IRQF_TRIGGER_RISING won't fix the issue triggering 2 times in keyboard interrupt when pressing a key
        if (request_irq(IRQ_1, (irq_handler_t) irq_1_handler, IRQF_SHARED|IRQF_TRIGGER_RISING, DEV_NAME, DEV_ID) != 0)

        2. Must have IRQF_SHARED to register interrupt 1 successfully. request_irq() will fail if only use IRQF_TRIGGER_RISING
        if (request_irq(IRQ_1, (irq_handler_t) irq_1_handler, IRQF_TRIGGER_RISING, DEV_NAME, DEV_ID) != 0) => this will fail
    */
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
	printk(KERN_INFO "clean up module\n");
}
