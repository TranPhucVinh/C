#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

#define KM_NAME     "insert_params"
#define STR_VALUE   "Modify param of this_module->name"

// struct param_attribute is defined internally inside linux/kernel/params.c
// copy struct param_attribute to this kernel module source code for parameters later parsing
struct param_attribute
{
	struct module_attribute mattr;
	const struct kernel_param *param;
};

// struct module_param_attrs is defined internally inside linux/kernel/params.c
// copy struct module_param_attrs to this kernel module source code for parameters later parsing
struct module_param_attrs
{
	unsigned int num;
	struct attribute_group grp;
	struct param_attribute attrs;
};

/*
    Read and update the parameters of a kernel module from the current one
    @km_name: Name of the kernel module to search to update its string parameters
    @str_value: String value to update
*/
void read_and_update_km_parameters(char *km_name, char *str_value){
    struct module *position;
    struct module_kobject search_module;
    struct module_param_attrs *_module_param_attrs;
    struct kernel_param *_kernel_param;
    struct kparam_string *_kparam_string;

	int index = 1;

    _module_param_attrs = (struct module_param_attrs *)kmalloc(sizeof(struct module_param_attrs), GFP_KERNEL);
    _kernel_param = (struct kernel_param *)kmalloc(sizeof(struct kernel_param), GFP_KERNEL);
    _kparam_string = (struct kparam_string *)kmalloc(sizeof(struct kparam_string), GFP_KERNEL);

	printk("THIS_MODULE has name %s\n", THIS_MODULE->name);

	list_for_each_entry(position, &(THIS_MODULE->list), list) {
		if (!strcmp(position->name, km_name)) {
            printk("Kernel module %d has name: %s\n", index, km_name);
            search_module = position->mkobj;
            break;
        }
        else index++;
	}

    _module_param_attrs = search_module.mp;
    _kernel_param = (_module_param_attrs->attrs).param;

    printk("Parameter's name: %s\n", _kernel_param->name);
    _kparam_string = _kernel_param->str;
    printk("Before changing, kernel param string value is: %s\n", _kparam_string->string);
    strcpy(_kparam_string->string, str_value);
    printk("After changing, kernel param string value is: %s\n", _kparam_string->string);
}

int init_module(void)
{
    read_and_update_km_parameters(KM_NAME, STR_VALUE);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
}