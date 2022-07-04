## Fundamental concepts

The frequency between 2 timers interrupt in kernel is called tick rate. Tick rate has a frequency of HZ hertz. Value HZ differs for each supported architecture. For example, by default the x86 architecture defines HZ to be 100.

High HZ results in finer kernel timer resolution but leads to more time that processor spends executing the timer interrupt.

``jiffies`` is the global variable which holds the number of ticks that have occurred since the system booted.

On boot, ``jiffies`` is set to ``0`` and it is incremented by one during each timer interrupt.

There are ``HZ`` timer interrupts in a second and there are ``HZ`` jiffies in a second so the system uptime is therefore ``jiffies/HZ`` seconds.

## API

``jiffies`` is defined in ``<linux/jiffies.h>``:

```c
extern unsigned long volatile jiffies;
```

Convert from seconds to a unit of ``jiffies``: ``seconds * HZ``. So expires time in timer will be ``jiffies + seconds * HZ``

Convert from miliseconds to a unit of ``jiffies``: ``msecs_to_jiffies(miliseconds) * HZ``. So expires time in timer will be ``jiffies + msecs_to_jiffies(miliseconds)``

Kernel timers are not cyclic. They are destroyed after they expires. Kernel timers are represented by ``struct timer_list`` which are defined in ``<linux/timer.h>``.

```c
struct timer_list {
        /*
         * All fields that change during normal runtime grouped to the
         * same cacheline
         */
        struct hlist_node       entry;
        unsigned long           expires;
        void                    (*function)(struct timer_list *);
        u32                     flags;

#ifdef CONFIG_LOCKDEP
        struct lockdep_map      lockdep_map;
#endif
};
```

```c
static inline void timer_setup(struct timer_list *timer,
                void (*callback)(struct timer_list *),
                unsigned int flags)
```

``mod_timer(timer, expires)``: Modify timer's timeout

``mod_timer(timer, expires)`` is equivalent to:

```c
del_timer(timer);
timer->expires = expires;
add_timer(timer);
```

``add_timer()`` will start a timer:

```c
void add_timer(struct timer_list *timer);
```

``del_timer()``: Delete timer. If not call ``del_timer()`` in cleanup module, the OS will then be frozen.

Get argument value of kernel timer by ``from_timer()``:

```c
#define from_timer(var, callback_timer, timer_fieldname) \
    container_of(callback_timer, typeof(*var), timer_fieldname) 
```

## Examples

* [kernel_timer_display_string.c](kernel_timer_display_string.c): Display a string in Kernel space every 1 second by timer
* [kernel_timer_arg.c](kernel_timer_arg.c): Get argument value of kernel timer

To setup timer in miliseconds:

```c
#define DELAY 		500 //ms

void timer_callback(struct timer_list* tl){
        /*
                Other operations like in kernel_timer_display_string.c
        */
	mod_timer(&kernel_timer, jiffies + msecs_to_jiffies(DELAY));
}

int init_module(void)
{
	/*
                Other operations like in kernel_timer_display_string.c
        */

	kernel_timer.expires = jiffies + msecs_to_jiffies(DELAY); //Delay at DELAY seconds for the 1st time

        /*
                Other operations like in kernel_timer_display_string.c
        */
}
```
