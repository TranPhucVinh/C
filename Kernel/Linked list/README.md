The Linux kernel support API to create a circular, doubly-linked lists.

# Implementations

## Create

Create and read all member of a linked list by ``list_add()``: [create_and_read_linked_list.c](create_and_read_linked_list.c)

With this source code, as the linked list is circular, next node of ``node_2`` will then be ``node_0``

Create a linked list by ``__list_add()``: Check [__list_add() API document](#__list_add)

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

**Read all member in an existing linked list with list_for_each_entry() (from node at index 1, not index 0)**: Check [list_for_each_entry() API](#list_for_each_entry) and [create_and_read_linked_list.c](create_and_read_linked_list.c).

**Read all members in an existing linked list by traversing in the while loop**:

```c
/**
 * display_linked_list - Display all members in the linked list through while loop 
 * and read_size
 * @first_node:
 * @read_size:
 */
void display_linked_list(struct data_base_node *first_node, int read_size){
    struct list_head *list_ptr = &(first_node->list);
	struct data_base_node *node_ptr;
	int node_count = 0;

	while(node_count < read_size)
	{
		node_ptr = list_entry(list_ptr, struct data_base_node, list);
		printk("node_%d has value %d\n", node_count, node_ptr->value);
		list_ptr = list_ptr->next;
		node_count += 1;
	}
}
```

This reading method has a drawback that the read_size argument must be updated everytime the linked list is appended or has its size reduced. It's better to use [list_for_each_entry()](#list_for_each_entry) instead.

**Read a node at specific index**

```c
//Other operations like in create_and_read_linked_list.c
void display_at_index(struct data_base_node *first_node, int index){
    struct list_head *list_ptr = &(first_node->list);
	struct data_base_node *position;

	int count_index = 1;
	if (index == 0)
	{
		printk("node_0 has value: %d\n", first_node->value);
		return;
	}
	list_for_each_entry(position, &(first_node->list), list) {
		if (count_index == index)
		{
			printk("node_%d has value: %d\n", index, position->value);
			return;
		}
		count_index++;
	}
	return;
}

int init_module(void)
{
    //Other operations like in create_and_read_linked_list.c
	display_linked_list(node_0);
	display_at_index(node_0, 0);
	display_at_index(node_0, 2);
	return 0;
}
//Other operations like in create_and_read_linked_list.c
```

## Update

Update node value at a specific index, view the node before and after updating to see changes: 

```c
//Other operations like in create_and_read_linked_list.c
void update_node(struct data_base_node *first_node, int index, int value){
    struct list_head *list_ptr = &(first_node->list);
	struct data_base_node *position;

	int count_index = 1;
	if (index == 0)
	{
		first_node->value = value;
		return;
	}
	list_for_each_entry(position, &(first_node->list), list) {
		if (count_index == index)
		{
			position->value = value;
			return;
		}
		count_index++;
	}
	return;
}

int init_module(void)
{
   //Other operations like in create_and_read_linked_list.c
	display_linked_list(node_0);

	update_node(node_0, 0, 12);
	display_linked_list(node_0);

	update_node(node_0, 1, 34);
	display_linked_list(node_0);
	return 0;
}
//Other operations like in create_and_read_linked_list.c
```

# API

### INIT_LIST_HEAD()

``INIT_LIST_HEAD()`` will init the list head of a circular linked list and must be used only 1 time in every circular linked list to create it.

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

### list_add()

```c
void list_add(struct list_head *new, struct list_head *head);
```
* ``struct list_head *new``: new entry to be added
* ``struct list_head *head``: list head to add it after

``list_add()`` will add a new entry at last index of a circular linked list during the forming/creating process.

``list_add()`` is defined from ``__list_add()``:

```c
void list_add(struct list_head *new, struct list_head *head) 
{ 
	__list_add(new, head, head->next); 
}
```

**Example**:

``list_add(&(node_2->list), &(node_1->list))`` will add ``node_1->list`` as the last element of the linked list. Then the next list of    ``node_1->list`` will link to the head node in that linked list to make the circular linked list. Check [create_and_read_linked_list.c](create_and_read_linked_list.c) with linked list creation process and the important comments for that.

**Note**: Must not use ``list_add()`` to insert a node by index to an existed linked list as this will break the existed node by breaking the last index node.

### __list_add()

Insert a new entry between two known consecutive entries.

```c
void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next);
```

**Create a linked list by __list_add()**

```c
//node_0, node_1 and node_2 are identically defined like in create_and_read_linked_list.c
INIT_LIST_HEAD(&(node_0->list));

__list_add(&(node_1->list), &(node_0->list), ((node_0->list).next));
__list_add(&(node_2->list), &(node_1->list), ((node_1->list).next));
```

**Note**: ``__list_add`` can be used to insert a node by index to an existed linked list.

### list_for_each_entry()

Iterate over list of given type (as a macro)

```c
#define list_for_each_entry(pos, head, member)	
```

Arguments:
* ``pos``: the type ``*`` to use as a loop cursor.
* ``head`` the head for your list.
* ``member`` the name of the list_head within the struct.

From this function definiton, we can see that it can only display the node from index 1, not from index 0.