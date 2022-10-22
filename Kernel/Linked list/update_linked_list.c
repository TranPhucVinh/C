#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

#define TOTAL_NODES	3

MODULE_LICENSE("GPL");

struct data_base_node {
    struct list_head list;
    int value;
};

struct data_base_node node_0, node_1, node_2, node_3;

void display_list(struct data_base_node first_node){
    struct list_head *list_ptr = &(first_node.list);
	struct data_base_node *node_ptr;
	int node_count = 0;

	while(node_count <= TOTAL_NODES)
	{
		node_ptr = list_entry(list_ptr, struct data_base_node, list);
		printk("node_%d has value %d\n", node_count, node_ptr->value);
		list_ptr = list_ptr->next;
		node_count += 1;
	}
}

/**
 * update_member - Update node's value by index
 * @first_node: As the first node not only involves in the linking process but
 * also is a member which can be updated, it must be passed by reference (pointer)
 * @index:
 * @value:
 */
void update_member(struct data_base_node *first_node, int index, int value){
    struct list_head *list_ptr = &(first_node->list);
	struct data_base_node *node_ptr;
	int node_count = 0;

	while(node_count <= TOTAL_NODES)
	{
		node_ptr = list_entry(list_ptr, struct data_base_node, list);
		if (node_count == index) {
			node_ptr->value = value;
			break;
		}
		list_ptr = list_ptr->next;
		node_count += 1;
	}
}

int init_module(void)
{
	node_0.value = 0;
	node_1.value = 1;
	node_2.value = 2;
	node_3.value = 3;

	INIT_LIST_HEAD(&node_0.list);

	list_add(&node_1.list, &node_0.list);
	list_add(&node_2.list, &node_1.list);
	list_add(&node_3.list, &node_2.list);

	printk(KERN_INFO "Setup link list\n");

	printk("Before updating:\n");
	display_list(node_0);

	update_member(&node_0, 2, 1234);

	printk("After updating:\n");
	display_list(node_0);
	return 0;
}

void cleanup_module(void)
{
	printk("Clean up module\n");	
}