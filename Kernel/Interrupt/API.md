# request_irq()

```c
#include <linux/interrupt.h>
int request_irq(unsigned int irq,	irq_handler_t handler, unsigned long flags,	const char *dev_name,	void *dev_id);
```
* ``unsigned int irq``: interrupt number being requested
* ``irq_handler_t (*handler)(int, void *, struct pt_regs *)``: pointer to the handling function being installed
* ``unsigned long flags``: flag which will trigger the interrupt
* ``const char *dev_name``: The string used in ``/proc/interrupts`` to show the owner of the interrupt
* ``void *dev_id``: Pointer used for shared interrupt lines. It is a unique identifier that is used when the interrupt line is freed and that may also be used by the driver to point to its own private data area (to identify which device is interrupting). If the interrupt is not shared, dev_id can be set to ``NULL``. Most of the time, ``dev_id`` will be pointer to the device driver's private data.

``flags`` value:

* ``IRQF_SHARED`` announces the kernel that the interrupt can be shared with other devices. If this flag is not set, then if there is already a handler associated with the requested interrupt, the request for interrupt will fail.

``irq_handler_t (*handler)(int, void *, struct pt_regs *)`` returns ``IRQ_HANDLED`` to indicates that the IRQ is handled successfully.  The return value of kernel IRQ handler function, generally, is used by the kernel to detect and suppress spurious interrupts and this return value has not thing to deal with the userspace.

# free_irq()

Free an interrupt allocated with ``request_irq``

```c
void free_irq (	unsigned int irq, void * dev_id);
```
# request_threaded_irq()

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

# devm_request_threaded_irq()

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

# devm_free_irq()

``devm_free_irq()`` works like ``free_irq()`` but it has to go with ``devm_request_threaded_irq()`` in the same program to avoid memory issue with currently used IRQ number when ``insmod`` and ``rmmod`` the module several times.

```c
void devm_free_irq(struct device *dev, unsigned int irq, void *dev_id);
```

# disable_irq() and enable_irq()

```c
void disable_irq (unsigned int irq);//Disable interrupt
void enable_irq (unsigned int irq);//Enable interrupt
```

* ``unsigned int irq``: Interrupt to enable
