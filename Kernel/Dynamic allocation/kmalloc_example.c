#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h> //for kmalloc()

MODULE_LICENSE("GPL");

int init_module(void)
{
	char *str;
    int *number, *int_array;

	/* Initial memory allocation */
	str = (char *) kmalloc(15, GFP_KERNEL);
	strcpy(str, "Learn malloc");
	printk(KERN_INFO "%s\n", str);
	kfree(str);
	printk(KERN_INFO "DEBUG: str after kfree(): %s\n", str);//DEBUG: str after kfree(): Learn malloc (str is not freed)

    number = (int *) kmalloc(1, GFP_KERNEL);
    *number = 123;
    printk(KERN_INFO "%d\n", *number);
	kfree(number);
	printk(KERN_INFO "DEBUG: number after kfree(): %d\n", *number);//-1222998076

    int_array = (int *) kmalloc(3, GFP_KERNEL);
    int_array[0] = 1;
    int_array[1] = 2;
    int_array[2] = 3;

    printk(KERN_INFO "%d %d %d\n", int_array[0], int_array[1], int_array[2]);
	kfree(int_array);
	printk(KERN_INFO "DEBUG %d %d %d\n", int_array[0], int_array[1], int_array[2]);//-1222998076 -1931286851 3
	return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
}
