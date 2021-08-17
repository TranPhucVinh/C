#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
        printk(KERN_INFO "Hello, World !\n");
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "clean up module\n");
}