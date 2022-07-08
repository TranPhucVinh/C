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
* ``void *dev_id``: Pointer used for shared interrupt lines. It is a unique identifier that is used when the interrupt line is freed and that may also be used by the driver to point to its own private data area (to identify which device is interrupting). If the interrupt is not shared, dev_id can be set to ``NULL``

# Examples

Check the corresponding example in Raspbian for [toggling LED by button using interrupt](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/toggle_led_by_interrupt.c).

After inserting that kernel module, the interrupt type with the specified device name (by macro ``DEV_NAME``) and the IRQ number (``int irq_number``) can be listed out by ``cat /proc/interrupts``.