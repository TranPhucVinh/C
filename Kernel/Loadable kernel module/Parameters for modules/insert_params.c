#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int number  = 9;
char *char_ptr  = "Char pointer as string";
char char_arr[]  = "Char array as string";

//Must be outside init_module()
module_param(number, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

/*
	charp: type char pointer for string. charp type must be used for string char pointer, not char array
*/
module_param(char_ptr, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

//char_array_as_string: is the name to be displayed on /sys/module/$(kernel_module_name)/parameters/ 
module_param_string(char_array_as_string, char_arr, sizeof(char_arr), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

int init_module(void)
{
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}