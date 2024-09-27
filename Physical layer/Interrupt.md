Interrupt is a **response by the processor to an event** that needs attention from the software. That event can be GPIO voltage level rising or falling, timer overflow,... Interrupts can be triggered internally – from a timer, for example – or externally, from peripherals.

An interrupt condition alerts the processor and serves as a request for the processor to interrupt the currently executing code when permitted, so that the event can be processed in a timely manner.

If the request is accepted, the processor responds by suspending its current activities, saving its state, and executing a function called an interrupt handler (or an interrupt service routine, ISR) to deal with the event

# ISR

An **ISR** (Interrupt Service Routine) is an interrupt handler, a callback subroutine (i.e a function) which is called when an interrupt is encountered. ISR does not return anything. An ISR returns nothing because there is no caller in the software to read the returned values.

We can use function inside ISR as long as that function is not invoked from other portion of the code.

**Interrupt latency** is the time required for an ISR responds to an interrupt.

Interrupt latency can be minimized by writing short ISR routine and by not delaying interrupts for more time.

For implementation of ISR, check the corresponding document in C and other MCU repositories, like AVR Arduino framework.

**Must not use printf() inside ISR**: ``printf()`` function in ISR is not supported because ``printf()`` function is not reentrant, thread safe and uses dynamic memory allocation which takes a lot of time and can affect the speed of an ISR up to a great extent.

**Can we put breakpoint inside ISR ?**: Putting a break point inside ISR is not a good idea because debugging will take some time and a difference of half or more seconds will lead to different behavior of hardware. To debug ISR, definitive logs are better.

# Linux interrupts

Linux interrupts is not architecture dependent. 

The number of available interrupts varies from as few as 15 on the SPARC to as many as 256 on the IA-64 and a few other systems. It’s interesting to note that the number of interrupts defined on the x86 is currently 224, as explained in ``include/asm-i386/irq.h``, depends on Linux using the architectural limit instead of an implementation-specific limit

Here is a list of the IRQs and their common purposes in the x86 system:

| IRQ | Usage |
| ------- |:------:|
| 0  | System timer (cannot be changed)|
| 1  | Keyboard controller (cannot be changed)|
| 12 | PS/2 mouse|

All Linux interrupts can be listed in ``/proc/interrupts``: ``cat /proc/interrupts``. Based on the interrupt numbers listed in this file, a small IRQ number value means higher priority. 

The ``/proc/interrupts`` display shows how many interrupts have been delivered to each CPU on the system.

Those are interrupts in an Ubuntu 20.04 WSL

```
username@hostname:~$ cat /proc/interrupts
           CPU0       CPU1       CPU2       CPU3       CPU4       CPU5       CPU6       CPU7
  8:          0          0          0          0          0          0          0          0   IO-APIC   8-edge      rtc0
  9:          0          0          0          0          0          0          0          0   IO-APIC   9-fasteoi   acpi
NMI:          0          0          0          0          0          0          0          0   Non-maskable interrupts
LOC:          0          0          0          0          0          0          0          0   Local timer interrupts
SPU:          0          0          0          0          0          0          0          0   Spurious interrupts
PMI:          0          0          0          0          0          0          0          0   Performance monitoring interrupts
IWI:          0          0          0          0          0          0          0          0   IRQ work interrupts
RTR:          0          0          0          0          0          0          0          0   APIC ICR read retries
RES:    1285454    1532367    1803913    1102039    1745163    1044726    1806928    1024616   Rescheduling interrupts
CAL:       8408      16785       7300       9238       6891       7631       7498       6001   Function call interrupts
TLB:          0          0          0          0          0          0          0          0   TLB shootdowns
HYP:    4149638         92      48073         30         22         24         44         24   Hypervisor callback interrupts
HRE:          0          0          0          0          0          0          0          0   Hyper-V reenlightenment interrupts
HVS:      56048      35510      75041      42863      65428      51369      62643      47317   Hyper-V stimer0 interrupts
ERR:          0
MIS:          0
PIN:          0          0          0          0          0          0          0          0   Posted-interrupt notification event
NPI:          0          0          0          0          0          0          0          0   Nested posted-interrupt event
PIW:          0          0          0          0          0          0          0          0   Posted-interrupt wakeup event
```

You can see from the IRQs that are missing that the file shows only interrupts corresponding to installed handlers. For example, the first serial port (which uses interrupt number 4) is not shown, indicating that the modem isn’t being used. In fact, even if the modem had been used earlier but wasn’t in use at the time of the snapshot, it would not show up in the file; the serial ports are well behaved and release their interrupt handlers when the device is closed.

## Timer interrupt

Timer interrupt with IRQ 0, is used for system timer. This is the reserved interrupt for the internal system timer. It is used exclusively for internal operations and is never available to peripherals or user devices. Kernel module function like ``request_irq()`` will return fail when trying to request it.

```c
#define IRQ_0         0		
if (request_irq(IRQ_0, (irq_handler_t) irq_0_handler, IRQF_TIMER|IRQF_SHARED, DEV_NAME, DEV_ID) != 0){
        printk("Can't request interrupt number %d\n", IRQ_0);
    } else printk("Request interrupt number %d successfully\n", IRQ_0);
```

This fails to register IRQ 0 (in ``dmesg``): ``Can't request interrupt number 0``

## i8042

The 8042 device, which has the IRQ name ``i8042``, implements the functionality of the 8042 keyboard controller together with a 104/105 key Windows 95 type keyboard, and a two button mouse.

For example, in a Ubuntu 16.04 laptop with a built-in keyboard and a built-in touchpad, ``i8042`` interrupt are:

```
            CPU0       CPU1       CPU2       CPU3       
   1:          0          0          0        136  IR-IO-APIC    1-edge      i8042,
  12:          0          0    1407260          0  IR-IO-APIC   12-edge      i8042
```

In that computer, IRQ 1 is used for the built-in keyboard interrupt while IRQ 12 is used for the touchpad interrupt. With the touchpad interrupt IRQ 12, every move on the keypad will then trigger it.
