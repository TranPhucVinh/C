#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h> //for kmalloc()

#define TOTAL_NODES	3

MODULE_LICENSE("GPL");

struct database_node {
    struct list_head list;
    int value;
};

typedef struct database_node database_node;
database_node *node_0, *node_1, *node_2;

void display_linked_list(struct database_node *first_node){
	struct database_node *position;
	int index = 1;

	//Display node 0
	printk("node_0 has value: %d\n", first_node->value);

	//Then display node from index 1 to n-1
	list_for_each_entry(position, &(first_node->list), list) {
		printk("node_%d has value: %d\n", index, position->value);
		index++;
	}
}

#define ENABLE_INSERT_HEAD

#if defined(ENABLE_INSERT_HEAD)
int insert_node_at_index(database_node** first_node, int index, int value)
#else
int insert_node_at_index(database_node* first_node, int index, int value)
#endif
{
	struct database_node *position, *ins_node;
	ins_node = (database_node *) kmalloc(sizeof(database_node), GFP_KERNEL);
	ins_node->value = value;
#if defined(ENABLE_INSERT_HEAD)
	if (index == 0)
	{
		INIT_LIST_HEAD(&ins_node->list);
		struct database_node *temp = *first_node;
		*first_node = ins_node;
		__list_add(&ins_node->list, temp->list.prev, &temp->list);
		return 0;
	}
	struct database_node *itr_list = *first_node;//iterate list
#else
	if (index == 0)
	{
		printk("Cant insert head node\n");
		kfree(ins_node);
		return -1;
	}
	struct database_node *itr_list = first_node;
#endif
	int count_index = 1;
	list_for_each_entry(position, &itr_list->list, list) {
		if (count_index == index)
		{
			__list_add(&ins_node->list, position->list.prev, &position->list);
			return 0;
		}
		count_index++;
	}
	kfree(ins_node);
	return -1;
}

int init_module(void)
{
    node_0 = (database_node *) kmalloc(sizeof(database_node), GFP_KERNEL);
    node_1 = (database_node *) kmalloc(sizeof(database_node), GFP_KERNEL);
    node_2 = (database_node *) kmalloc(sizeof(database_node), GFP_KERNEL);

	node_0->value = 1;
	node_1->value = 2;
	node_2->value = 3;

	INIT_LIST_HEAD(&(node_0->list));

	printk(KERN_INFO "Before inserting:\n");
	list_add(&(node_1->list), &(node_0->list));
	list_add(&(node_2->list), &(node_1->list));
	/*
		list_add(&(node_2->list), &(node_1->list)) will add node_1->list as the last element of the linked list. 
		Then the next list of node_1->list will link to node_0, the head node in that linked list to make the circular linked list.
	*/
	display_linked_list(node_0);

	// insert_node_at_index(node_0, 1, 123);
	insert_node_at_index(&node_0, 0, 123);//Insert head node

	printk(KERN_INFO "After inserting:\n");
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
