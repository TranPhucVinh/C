#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int number  = 9;
int int_arr[] = {1, 2};
char *char_ptr  = "Char pointer as string";
char char_arr[]  = "Char array as string";
// int arr_argc = 0;

//Must be outside init_module()
module_param(number, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

/*
	If setting the third parameter to a variable like arr_argc, kernel param int_arr isn't displayed
	in /sys/module/$(kernel_module_name)/parameters/ 
*/
// module_param_array(int_arr, int, &arr_argc, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

/*
	Set the third parameter to NULL so that kernel param int_arr is displayed in
	/sys/module/$(kernel_module_name)/parameters/ 
*/
module_param_array(int_arr, int, NULL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

/*
	charp: type char pointer for string. charp type must be used for string char pointer, not char array
*/
module_param(char_ptr, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

//char_array_as_string: is the name to be displayed on /sys/module/$(kernel_module_name)/parameters/ 
module_param_string(char_array_as_string, char_arr, sizeof(char_arr), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

int init_module(void)
{
    // printk("%d\n", arr_argc);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}
