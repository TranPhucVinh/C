#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h> //for kmalloc()

#define TOTAL_NODES	3

MODULE_LICENSE("GPL");

struct data_base_node {
    struct list_head list;
    int value;
};

typedef struct data_base_node data_base_node;
data_base_node *node_0, *node_1, *node_2;

void display_list(struct data_base_node first_node){
    struct list_head *list_ptr = &(first_node.list);
	struct data_base_node *node_ptr;
	int node_count = 0;

	while(node_count < TOTAL_NODES)
	{
		node_ptr = list_entry(list_ptr, struct data_base_node, list);
		printk("node_%d has value %d\n", node_count, node_ptr->value);
		list_ptr = list_ptr->next;
		node_count += 1;
	}
}

int init_module(void)
{
    node_0 = (data_base_node *) kmalloc(sizeof(data_base_node), GFP_KERNEL);
    node_1 = (data_base_node *) kmalloc(sizeof(data_base_node), GFP_KERNEL);
    node_2 = (data_base_node *) kmalloc(sizeof(data_base_node), GFP_KERNEL);

	node_0->value = 1;
	node_1->value = 2;
	node_2->value = 3;

	INIT_LIST_HEAD(&(node_0->list));

	list_add(&(node_1->list), &(node_0->list));
	list_add(&(node_2->list), &(node_1->list));
	printk(KERN_INFO "Setup link list\n");

	display_list(*node_0);
	return 0;
}

void cleanup_module(void)
{
    kfree(node_0);
    kfree(node_1);
    kfree(node_2);
	printk("Clean up module\n");	
}