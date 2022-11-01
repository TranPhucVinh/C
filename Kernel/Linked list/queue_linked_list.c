#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h> //for kmalloc()

MODULE_LICENSE("GPL");
LIST_HEAD(linkedlist);//Define linkedlist as global variable

struct database_node {
    struct list_head list;
    int value;
};

typedef struct database_node database_node;
database_node *node_0, *node_1, *node_2;

void display_linked_list(void){
    struct database_node *position;
	int index = 0;

	//Then display node from index 1 to n-1
	list_for_each_entry(position, &linkedlist, list) {
		printk("node_%d has value: %d\n", index, position->value);
		index++;
	}
}

int init_module(void)
{
    node_0 = (database_node *) kmalloc(sizeof(database_node), GFP_KERNEL);
    node_1 = (database_node *) kmalloc(sizeof(database_node), GFP_KERNEL);
    node_2 = (database_node *) kmalloc(sizeof(database_node), GFP_KERNEL);

	node_0->value = 12;
	node_1->value = 34;
	node_2->value = 56;

	//By creating the linkedlist with LIST_HEAD(linkedlist), linkedlist will be 
	//treated as a queue. Use list_add_tail() to add data to that queue

	printk(KERN_INFO "Setup link list\n");
	list_add_tail(&(node_0->list), &linkedlist);
	list_add_tail(&(node_1->list), &linkedlist);
	list_add_tail(&(node_2->list), &linkedlist);

	display_linked_list();
	return 0;
}

void cleanup_module(void)
{
    kfree(node_0);
    kfree(node_1);
    kfree(node_2);
	printk("Clean up module\n");	
}
