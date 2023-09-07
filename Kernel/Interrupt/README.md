# Fundamental concepts

When interrupt triggers, the interrupt handler should be executed very quickly and it should not run for more time (it should not perform time-consuming tasks). If we have the interrupt handler who is doing more tasks then we need to divide it into two halves:

1. Top Half
2. Bottom Half

The top half is our interrupt handler. If not much work is required, then the top half is enough. But if we have more work when interrupt is triggered, then we need the bottom half.  

Threaded IRQ is a technique used for bottom half which is implemented by ``request_threaded_irq()``.

# API

## request_irq()

```c
#include <linux/interrupt.h>
int request_irq(unsigned int irq,
	irq_handler_t handler,
	unsigned long flags,
	const char *dev_name,
	void *dev_id)
```
* ``unsigned int irq``: interrupt number being requested
* ``irq_handler_t (*handler)(int, void *, struct pt_regs *)``: pointer to the handling function being installed
* ``unsigned long flags``: flag which will trigger the interrupt
* ``const char *dev_name``: The string used in ``/proc/interrupts`` to show the owner of the interrupt
* ``void *dev_id``: Pointer used for shared interrupt lines. It is a unique identifier that is used when the interrupt line is freed and that may also be used by the driver to point to its own private data area (to identify which device is interrupting). If the interrupt is not shared, dev_id can be set to ``NULL``. Most of the time, ``dev_id`` will be pointer to the device driver's private data.

``flags`` value:

* ``IRQF_SHARED`` announces the kernel that the interrupt can be shared with other devices. If this flag is not set, then if there is already a handler associated with the requested interrupt, the request for interrupt will fail.

``irq_handler_t (*handler)(int, void *, struct pt_regs *)`` returns ``IRQ_HANDLED`` to indicates that the IRQ is handled successfully.  The return value of kernel IRQ handler function, generally, is used by the kernel to detect and suppress spurious interrupts and this return value has not thing to deal with the userspace.

## free_irq()

Free an interrupt allocated with ``request_irq``

```c
void free_irq (	unsigned int irq, void * dev_id);
```

## request_threaded_irq()

```c
int request_threaded_irq(unsigned int irq, 
	irq_handler_t handler,
	irq_handler_t thread_fn,
	unsigned long irqflags,
	const char *devname,
	void *dev_id);
```

* ``handler``: If it returns ``IRQ_WAKE_THREAD``, then the kernel calls the ``thread_fn``
* ``thread_fn``: A function called from the IRQ ``handler``. If ``NULL``, no IRQ thread is created. This represents the bottom half. When the handler function returns ``IRQ_WAKE_THREAD``, the ``kthread`` associated with this bottom half will be scheduled and ``thread_fn`` will be called. The ``thread_fn`` function must return ``IRQ_HANDLED`` when complete. After being executed, the ``kthread`` will not be rescheduled again until the IRQ is triggered again and the handler returns ``IRQ_WAKE_THREAD``.

**Example**: Haven't implemented example for this API, check [the corresponding example in character device with devm_request_threaded_irq()](interrupt_for_character_device.c)

## devm_request_threaded_irq()

``devm_request_threaded_irq()`` is used to handle interrupt for character device.

Except for the extra argument, ``devm_request_threaded_irq()`` takes the same arguments and performs the same function as ``request_irq()``.

```c
int devm_request_threaded_irq	(	
	struct device * 	dev,
	unsigned int 	irq,
	irq_handler_t 	handler,
	irq_handler_t 	thread_fn,
	unsigned long 	irqflags,
	const char * 	devname,
	void * 	dev_id 
)	
```

* ``thread_fn``: function to be called in a threaded interrupt context, ``NULL`` for devices which handle everything

## devm_free_irq()

``devm_free_irq()`` works like ``free_irq()`` but it has to go with ``devm_request_threaded_irq()`` in the same program to avoid memory issue with currently used IRQ number when ``insmod`` and ``rmmod`` the module several times.

```c
void devm_free_irq(struct device *dev, unsigned int irq, void *dev_id);
```

## disable_irq() and enable_irq()

```c
void disable_irq (unsigned int irq);//Disable interrupt
void enable_irq (unsigned int irq);//Enable interrupt
```

* ``unsigned int irq``: Interrupt to enable

# Examples

## Interrupt 1 (keyboard interrupt)

**Feature**: Count how many times the keyboard is pressed on Ubuntu by using interrupt 1

**Program**: [keyboard_interrupt.c](keyboard_interrupt.c)

**Result**: After inserting this kernel module, the ``DEV_NAME`` registered in ``request_irq()`` appeared in IRQ 1 (``/proc/interrupts``)

```
        CPU0       CPU1       CPU2       CPU3       
0:         13          0          0          0  IR-IO-APIC    2-edge      timer
1:          0          0          0        157  IR-IO-APIC    1-edge      i8042, DEV_NAME IRQ_1
```

**Note**:

* Every time a key is pressed, 2 interrupts will be triggered. Even if handling with flags like ``IRQF_SHARED|IRQF_TRIGGER_RISING``, that issue still happen
* The keyboard interrupt can only be triggered by the built-in keyboard of the PC, not from the USB keyboard connected to PC.

## GPIO interrupt

Check the implementation in Raspbian for [toggling LED by button using interrupt](https://github.com/TranPhucVinh/Raspberry-Pi-GNU/blob/main/Kernel/GPIO/toggle_led_by_gpio_interrupt.c).

After inserting that kernel module, the interrupt type with the specified device name (by macro ``DEV_NAME``) and the IRQ number (``int irq_number``) can be listed out by ``cat /proc/interrupts``.

## Disable and enable interrupt

Kernel interrupt can't be disable and enable directly from userspace process. Only kernel module can disable a specific interrupt by ``disable_irq()`` function and enable by ``enable_irq()``

Program ``disable_interrupt.c`` below will disable interrupt 1 as the built-in keyboard and touchpad are disable (USB connected keyboard and mouse still work normally, we can use the key on USB connected keyboard to ``rmmod`` the kernel module). Running ``rmmod`` to the module will enable interrupt 1 again.

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

#define IRQ_NUM    1

int init_module(void)
{
	printk(KERN_INFO "Module to disable interrupt\n");
	disable_irq(IRQ_NUM);

	return 0;
}

void cleanup_module(void)
{
	enable_irq(IRQ_NUM);
	printk(KERN_INFO "clean up module disable interrupt\n");
}
```

**Note**: If inserting kernel module ``disable_interrupt`` before inserting ``keyboard_interrupt``,  ``keyboard_interrupt`` is still able to register interrupt 1 successfully although interrupt 1 is disable by ``disable_interrupt``.

## Interrupt for character device: Count how many times the keyboard is pressed on Ubuntu by using interrupt 1

Program: [interrupt_for_character_device.c](interrupt_for_character_device.c)

Register to interrupt 1 every time file operation open is called (by ``cat /dev/fops_character_device``):

```c
//Other operations are like interrupt_for_character_device.c
int dev_open(struct inode *inodep, struct file *filep)
{
    if (devm_request_threaded_irq(device, IRQ_1, (irq_handler_t) irq_1_handler, (irq_handler_t) THREAD_FN, IRQF_SHARED, INTERRUPT_NAME, INTERRUPT_ID) != 0){
        printk("Can't request interrupt number %d\n", IRQ_1);
    } else printk("Request interrupt number %d successfully\n", IRQ_1);
	return 0;
}
//Other operations are like interrupt_for_character_device.c
```

**Result**: Although interrupt 1 is registered every time calling open file operation by ``cat /dev/fops_character_device`` but variable ``pressed_times`` still increase its value every time interrupt 1 is triggered.

```
devm_request_threaded_irq; keyboard interrupt occured 1 times
devm_request_threaded_irq; keyboard interrupt occured 2 times
devm_request_threaded_irq; keyboard interrupt occured 3 times	
devm_request_threaded_irq; keyboard interrupt occured 4 times	
Request interrupt number 1 successfully
devm_request_threaded_irq; keyboard interrupt occured 5 times
devm_request_threaded_irq; keyboard interrupt occured 6 times
devm_request_threaded_irq; keyboard interrupt occured 7 times	
devm_request_threaded_irq; keyboard interrupt occured 8 times	
Request interrupt number 1 successfully
....
```

Use IRQ thread parameter in ``devm_request_threaded_irq()``:

```c
//Other operations are like interrupt_for_character_device.c
int pressed_times = 0;

irq_handler_t irq_1_handler(unsigned int irq, void* dev_id, struct pt_regs *regs){
    return (irq_handler_t) IRQ_WAKE_THREAD;
}

irq_handler_t thread_handler(unsigned int irq, void* dev_id, struct pt_regs *regs){
	printk("thread_handler is called; keyboard interrupt occured %d times\n", pressed_times);
	pressed_times += 1;
    return (irq_handler_t) IRQ_HANDLED;
}

int init_module(void)
{
	//Other operations are like interrupt_for_character_device.c

	//Must have irq_1_handler parameter value
    if (devm_request_threaded_irq(device, IRQ_1, (irq_handler_t) irq_1_handler, (irq_handler_t) thread_handler, IRQF_SHARED, INTERRUPT_NAME, INTERRUPT_ID) != 0){
        printk("Can't request interrupt number %d\n", IRQ_1);
    } else printk("Request interrupt number %d successfully\n", IRQ_1);

	return 0;
}
//Other operations are like interrupt_for_character_device.c
```
## Interrupt for character device: Count, enable and disable interrupt 1

**Features**
* Handle interrupt 1 like in example 1
* Disable and enable interrupt 1 from userspace through ``ioctl()``

Kernel module program [disable_enable_interrupt_for_character_device.c](disable_enable_interrupt_for_character_device.c)

User space program [ioctl_disable_enable_interrupt.c](ioctl_disable_enable_interrupt.c)
