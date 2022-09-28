The Linux kernel support API to create a circular, doubly-linked lists.

# Implementations

## Create

Create and read all member of a linked list: [create_and_read_linked_list.c](create_and_read_linked_list.c)

With this source code, as the linked list is circular, next node of ``node_2`` will then be ``node_0``

Can't setup linked list like this:

```c
struct data_base_node node_0, node_1, node_2;

INIT_LIST_HEAD(&node_0.list);
node_0.list.next = node_1.list.prev;
node_1.list.next = node_2.list.prev;
node_2.list.next = node_0.list.prev;
```

This will cause the module to crash. Even when removing ``INIT_LIST_HEAD()`` setup, the module crashing issue still happen.

## Read

Read a node at specific index

```c
//Other operations like in create_and_read_linked_list.c
void read_member(struct data_base_node *first_node, int index){
    struct list_head *list_ptr = &(first_node.list);
	struct data_base_node *node_ptr;
	int node_count = 0;

	while(node_count <= TOTAL_NODES)
	{
		node_ptr = list_entry(list_ptr, struct data_base_node, list);
		if (node_count == index) {
			printk("node_%d has value %d\n", node_count, node_ptr->value);
			break;
		}
		list_ptr = list_ptr->next;
		node_count += 1;
	}
}

int init_module(void)
{
	//Other operations like in create_and_read_linked_list.c
	read_member(node_0, 2);
	return 0;
}
//Other operations like in create_and_read_linked_list.c
```

## Update

Update node value at a specific index, view the node before and after updating to see changes: [update_linked_list.c](update_linked_list.c)

# API

### list_head()

```c
struct list_head {
    struct list_head *next, *prev;
};
```

### list_entry()

```c
list_entry(struct list_head *ptr, type_of_struct, field_name);
```

``list_entry`` will map a ``list_head`` structure pointer back into a pointer to the structure that contains it.