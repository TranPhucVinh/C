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

void display_linked_list(struct data_base_node *first_node){
    struct data_base_node *position;
	int index = 1;

	//Display node 0
	printk("node_0 has value: %d\n", first_node->value);

	//Then display node from index 1 to n-1
	list_for_each_entry(position, &(first_node->list), list) {
		printk("node_%d has value: %d\n", index, position->value);
		index++;
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

	printk(KERN_INFO "Setup link list\n");
	list_add(&(node_1->list), &(node_0->list));
	list_add(&(node_2->list), &(node_1->list));
	/*
		list_add(&(node_2->list), &(node_1->list)) will add node_1->list as the last element of the linked list. 
		Then the next list of node_1->list will link to node_0, the head node in that linked list to make the circular linked list.
	*/
	display_linked_list(node_0);
	return 0;
}

void cleanup_module(void)
{
    kfree(node_0);
    kfree(node_1);
    kfree(node_2);
	printk("Clean up module\n");	
}
