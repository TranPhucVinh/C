#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int number  = 9;

int     param_set(const char *val, const struct kernel_param *kp);
int     param_get(char *buf, const struct kernel_param *kp);
void    param_free(void *arg);

struct kernel_param_ops km_param_ops = 
{
    .set = &param_set,
    .get = &param_get,
    .free = &param_free
};

//When using module_param_cb, don't use module_param()
module_param_cb(number, &km_param_ops, &number, S_IRUGO|S_IWUSR);

int init_module(void)
{
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "clean up module\n");
}

/*  
    Setting kernel parameter number like echo 123 > /sys/module/<km_name>/parameters/number
    will trigger this function
*/
int param_set(const char *val, const struct kernel_param *kp)
{
    int res = param_set_int(val, kp);
    if(res==0) {
        printk(KERN_INFO "param_set() is called for km_param number\n");
        printk(KERN_INFO "New value for km_param number: %d\n", number);
        return 0;
    }
    return -1;
}

/*  
    Read kernel parameter number like cat /sys/module/<km_name>/parameters/number
    will trigger this function
*/
int param_get(char *buf, const struct kernel_param *kp){
    printk(KERN_INFO "param_get() is called for km_param number\n");
    printk(KERN_INFO "%s\n", buf);//NULL
    return 0;
}

// Remove the whole kernel module will trigger this function
void param_free(void *arg)
{
    printk(KERN_INFO "free param\n");
}
