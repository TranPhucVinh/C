# API

```c
#include <linux/interrupt.h>
int request_irq(unsigned int irq,
    irqreturn_t (*handler)(int, void *, struct pt_regs *),
    unsigned long flags,
    const char *dev_name,
    void *dev_id);
```

* ``unsigned int irq``: interrupt number being requested
* ``irqreturn_t (*handler)(int, void *, struct pt_regs *)``: pointer to the handling function being installed
* ``unsigned long flags``: flag which will trigger the interrupt
* ``const char *dev_name``: The string used in ``/proc/interrupts`` to show the owner of the interrupt
* ``void *dev_id``: Pointer used for shared interrupt lines. It is a unique identifier that is used when the interrupt line is freed and that may also be used by the driver to point to its own private data area (to identify which device is interrupting). If the interrupt is not shared, dev_id can be set to ``NULL``. Most of the time, ``dev_id`` will be pointer to the device driver's private data.

``flags`` value:

* ``IRQF_SHARED`` announces the kernel that the interrupt can be shared with other devices. If this flag is not set, then if there is already a handler associated with the requested interrupt, the request for interrupt will fail.

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

Check the corresponding example in Raspbian for [toggling LED by button using interrupt](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/toggle_led_by_gpio_interrupt.c).

After inserting that kernel module, the interrupt type with the specified device name (by macro ``DEV_NAME``) and the IRQ number (``int irq_number``) can be listed out by ``cat /proc/interrupts``.

## Disable and enable interrupt

Kernel interrupt can't be disable and enable directly from userspace process. Only kernel module can disable a specific interrupt by ``disable_irq()`` function and enable by ``enable_irq()``

This program will disable interrupt 1 as the built-in keyboard and touchpad are disable (USB connected keyboard and mouse still work normally, we can use the key on USB connected keyboard to ``rmmod`` the kernel module). Running ``rmmod`` to the module will enable interrupt 1 again.

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