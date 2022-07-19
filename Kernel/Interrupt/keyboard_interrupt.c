#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define LED			3
#define BUTTON		2

#define DEV_NAME    "DEV_NAME IRQ_1"
#define DEV_ID      NULL

#define IRQ_1		1

MODULE_LICENSE("GPL");

int pressed_times = 0;

irq_handler_t irq_1_handler(unsigned int irq, void* dev_id, struct pt_regs *regs){
	printk("Keyboard interrupt occured %d\n", pressed_times);
	pressed_times += 1;
    return (irq_handler_t) IRQ_HANDLED;
}

int init_module(void)
{
	printk(KERN_INFO "Hello, World !\n");

    if(gpio_direction_input(BUTTON)){
        printk("Unable to set GPIO %d to input\n", BUTTON);
    }

    if (request_irq(IRQ_1, (irq_handler_t) irq_1_handler, IRQF_SHARED, DEV_NAME, (void*)irq_1_handler) != 0){// Must have (void*)irq_1_handler as the last argument to register interrupt

    /*
        Notes:
        1. Use OR flag IRQF_SHARED|IRQF_TRIGGER_RISING won't save the trigger 2 times in keyboard interrupt when pressing a button
        2.
        Must have (void*)irq_1_handler as the last argument to register interrupt
        if (request_irq(IRQ_1, (irq_handler_t) irq_1_handler, IRQF_SHARED|IRQF_TRIGGER_RISING, DEV_NAME, (void*)irq_1_handler) != 0)

        3. Must have IRQF_SHARED to register interrupt 1 successfully. request_irq() will fail if only use IRQF_TRIGGER_RISING
        if (request_irq(IRQ_1, (irq_handler_t) irq_1_handler, IRQF_TRIGGER_RISING, DEV_NAME, DEV_ID) != 0) => this will fail
    */
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
	free_irq(IRQ_1, (void*)irq_1_handler);
	printk(KERN_INFO "clean up module\n");
}