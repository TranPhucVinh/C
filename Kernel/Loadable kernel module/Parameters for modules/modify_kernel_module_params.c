#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

#define KM_NAME     "insert_params"
#define STR_VALUE   "Modify param of this_module->name"
#define ARR_NAME    "int_arr"

typedef struct module_kobject module_object;

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
	unsigned int num;// number of kernel parameters of the kernel module
	struct attribute_group grp;
	struct param_attribute attrs[];
};

int  search_for_km(char *km_name, module_object *search_module);
int  list_all_km_params(char *km_name);
void read_and_update_km_parameters(char *km_name, char *str_value);
void read_and_update_array_km_parameters(char *km_name, char *param_name, int index, int value);

int init_module(void)
{
    list_all_km_params(KM_NAME);
    read_and_update_km_parameters(KM_NAME, STR_VALUE);
    read_and_update_array_km_parameters(KM_NAME, ARR_NAME, 0, 1);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
}

/*
    Search for kernel modules
    @km_name: Name of the kernel module to search to update its string parameters
    @search_module:
*/
int search_for_km(char *km_name, module_object *search_module){
    struct module *position;
    int index = 1;

	printk("THIS_MODULE has name %s\n", THIS_MODULE->name);

	list_for_each_entry(position, &(THIS_MODULE->list), list) {
		if (!strcmp(position->name, km_name)) {
            printk("Kernel module %d has name: %s\n", index, km_name);
            memcpy(search_module, &(position->mkobj), sizeof(module_object));
            return 1;
        }
        else index++;
	}
    return 0;
}

/*
    List all parameters of the searched kernel module
    @km_name: Name of the kernel module to search to update its string parameters
*/
int list_all_km_params(char *km_name){
    struct module_param_attrs   *_module_param_attrs;
    struct kernel_param         *_kernel_param;
    module_object               *_search_module;

    _search_module = (module_object*)kmalloc(sizeof(module_object), GFP_KERNEL);
    _module_param_attrs = (struct module_param_attrs *)kmalloc(sizeof(struct module_param_attrs), GFP_KERNEL);
    _kernel_param = (struct kernel_param *)kmalloc(sizeof(struct kernel_param), GFP_KERNEL);

    if (search_for_km(km_name, _search_module)) {
        printk("Found %s\n", km_name);
        _module_param_attrs = _search_module->mp;
        printk("Total parameters of %s is %d\n", km_name, _module_param_attrs->num);
        int i = 0;
        for (i = 0; i < _module_param_attrs->num; i++){
            printk("%s", ((_module_param_attrs->attrs[i]).param)->name);
        }
        return 1;
    }
    else {
        printk("%s not existed or hasn't been inserted\n", km_name);
        return 0;
    }
}

/*
    Read and update the parameters of a kernel module from the current one
    @km_name: Name of the kernel module to search to update its string parameters
    @str_value: String value to update
*/
void read_and_update_km_parameters(char *km_name, char *str_value){
    struct kernel_param     *_kernel_param;
    struct kparam_string    *_kparam_string;
    module_object           *_search_module;

    _search_module = (module_object*)kmalloc(sizeof(module_object), GFP_KERNEL);
    _kernel_param = (struct kernel_param *)kmalloc(sizeof(struct kernel_param), GFP_KERNEL);
    _kparam_string = (struct kparam_string *)kmalloc(sizeof(struct kparam_string), GFP_KERNEL);

    if (search_for_km(km_name, _search_module)) {
        printk("Found %s\n", km_name);
        _kernel_param = (_search_module->mp->attrs)->param;

        printk("Parameter's name: %s\n", _kernel_param->name);
        memcpy(_kparam_string, _kernel_param->str, _kernel_param->str->maxlen);
        printk("Before changing, kernel param string value is: %s\n", _kparam_string->string);
        strcpy(_kparam_string->string, str_value);
        printk("After changing, kernel param string value is: %s\n", _kparam_string->string);
    }
    else printk("%s not existed or hasn't been inserted\n", km_name);
}

/*
    Read and update the array parameters of a kernel module from the current one
    @km_name: Name of the kernel module to search to update its string parameters
    @param_name: Name of the array parameters of the kernel module
    @index: index inside the array to be update
    @value:
*/
void read_and_update_array_km_parameters(char *km_name, char *param_name, int index, int value){
    module_object               *_search_module;
    struct module_param_attrs   *_module_param_attrs;
    struct kernel_param         *_kernel_param;
    struct kparam_array         *_kparam_array;

    _search_module = (module_object*)kmalloc(sizeof(module_object), GFP_KERNEL);
    _module_param_attrs = (struct module_param_attrs *)kmalloc(sizeof(struct module_param_attrs), GFP_KERNEL);
    _kernel_param = (struct kernel_param *)kmalloc(sizeof(struct kernel_param), GFP_KERNEL);
    _kparam_array = (struct kparam_array *)kmalloc(sizeof(struct kparam_array), GFP_KERNEL);

    if (search_for_km(km_name, _search_module)) {
        printk("Found %s\n", km_name);
        _module_param_attrs = _search_module->mp;
        int i = 0, j = 0;
        for (i = 0; i < _module_param_attrs->num; i++){
            if (!strcmp(((_module_param_attrs->attrs[i]).param)->name, param_name)){
                _kernel_param = (_module_param_attrs->attrs[i]).param;
                memcpy(_kparam_array, _kernel_param->arr, sizeof(struct kparam_array));

                printk("Total member: %d, size of each member %d\n", _kparam_array->max, _kparam_array->elemsize);
                int array[_kparam_array->max];
                memcpy(array, _kparam_array->elem, _kparam_array->max * _kparam_array->elemsize);

                printk("Array member before updating:");
                for (j = 0; j < _kparam_array->max; j++){
                    printk("%d\n", array[j]);
                }
                
                array[index]=value;
                printk("Array member after updating:");
                for (j = 0; j < _kparam_array->max; j++){
                    printk("%d\n", array[j]);
                }
            }
        }
    }
    else printk("%s not existed or hasn't been inserted\n", km_name);
}