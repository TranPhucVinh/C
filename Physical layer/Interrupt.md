## ISR

**Can we use printf() inside ISR ?**: ``printf()`` function in ISR is not supported because ``printf()`` function is not reentrant, thread safe and uses dynamic memory allocation which takes a lot of time and can affect the speed of an ISR up to a great extent.

**Can we put breakpoint inside ISR ?**: Putting a break point inside ISR is not a good idea because debugging will take some time and a difference of half or more seconds will lead to different behavior of hardware. To debug ISR, definitive logs are better.
