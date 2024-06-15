# INIT_LIST_HEAD()

``INIT_LIST_HEAD()`` will init the list head of a circular linked list and must be used only 1 time in every circular linked list to create it.

# list_head()

```c
struct list_head {
    struct list_head *next, *prev;
};
```

# list_entry()

```c
list_entry(struct list_head *ptr, type_of_struct, field_name);
```

``list_entry`` will map a ``list_head`` structure pointer back into a pointer to the structure that contains it.

# list_add()

```c
void list_add(struct list_head *new, struct list_head *head);
```
Insert a new entry after the specified head. This is useful for implementing **stacks**.
* ``struct list_head *new``: new entry to be added
* ``struct list_head *head``: list head to add it **after** (be not to confuse with ``list_add_tail()``)

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

# __list_add()

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

# list_add_tail()

```c
void list_add_tail(struct list_head *new, struct list_head *head);
```

Insert a new entry before the specified head. This is useful for implementing **queues**.

Arguments
* ``struct list_head *new``: new entry to be added
* ``struct list_head *head``: list head to add it **before** (be not to confuse with ``list_add()``)

# list_for_each_entry()

Iterate over list of given type (as a macro)

```c
#define list_for_each_entry(pos, head, member)	
```

Arguments:
* ``pos``: the type ``*`` to use as a loop cursor.
* ``head`` the head for your list.
* ``member`` the name of the list_head within the struct.

From this function definiton, we can see that it can only display the node from index 1, not from index 0.
