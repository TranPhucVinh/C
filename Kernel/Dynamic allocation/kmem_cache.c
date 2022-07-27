#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#define ALIGN_VALUE		0
#define CONSTRUCTOR	NULL	

MODULE_LICENSE("GPL");

struct kmem_cache *kmem_cache;

int init_module(void)
{
	char *str;
    int *number, *int_array;

	//Currently randomly choose SLAB_POISON without knowing for sure its purpose
	kmem_cache = kmem_cache_create("slab cache for string", 15, ALIGN_VALUE, SLAB_POISON, CONSTRUCTOR);
	str = (char *)kmem_cache_alloc(kmem_cache, GFP_KERNEL);

	strcpy(str, "Learn malloc");

	printk(KERN_INFO "%s\n", str);//Learn malloc
	kmem_cache_free(kmem_cache, str);

	/*
		Must use kmem_cache_destroy() to destroy the slab cache for
		later use
	*/
	kmem_cache_destroy(kmem_cache);
	printk(KERN_INFO "DEBUG: str after kmem_cache_free(): %s\n", str);
	/*DEBUG: str after kmem_cache_free(): kkkkkkkkkkkkkk\xa5Z\x88\xa2(\x92\xbc\xff2kkkkkkkkkkkkkk\xa5Z\ */
	
	//Currently randomly choose SLAB_POISON without knowing for sure its purpose
	kmem_cache = kmem_cache_create("slab cache for int", 1, ALIGN_VALUE, SLAB_POISON, CONSTRUCTOR);
	number = (int *) kmem_cache_alloc(kmem_cache, GFP_KERNEL);
	*number = 123;
	printk(KERN_INFO "%d\n", *number);//123
	kmem_cache_free(kmem_cache, number);
	kmem_cache_destroy(kmem_cache);
	printk(KERN_INFO "DEBUG: number after kfree(): %d\n", *number);//DEBUG: number after kfree(): 165
	
	kmem_cache = kmem_cache_create("slab cache for int array", 3, ALIGN_VALUE, SLAB_POISON, CONSTRUCTOR);
    int_array = (int *) kmem_cache_alloc(kmem_cache, GFP_KERNEL);
    int_array[0] = 1;
    int_array[1] = 2;
    int_array[2] = 3;

    printk(KERN_INFO "%d %d %d\n", int_array[0], int_array[1], int_array[2]);//1 2 3
	kmem_cache_free(kmem_cache, int_array);
	kmem_cache_destroy(kmem_cache);
	printk(KERN_INFO "DEBUG %d %d %d\n", int_array[0], int_array[1], int_array[2]);//DEBUG 10840939 2 2027256
	return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "clean up module\n");
}