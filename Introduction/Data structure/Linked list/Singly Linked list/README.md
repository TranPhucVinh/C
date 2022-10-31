# Fundamental concept

### Structure of a Singly Linked list data structure

```
Node 1 -> Node 2 -> Node 3 -> ... -> NULL
```

For memory storage reason, linked list must be implemented on heap memory.

### Why can't use linked list in stack memory

This program will insert new node and display link list successfully. For ``insert_node_at_middle()``, this function can only be called one time as using ``static struct database_node`` so its address can't be changed in the next time calling this function:

```c
//Must not implement linked list on stack memory like this program
#include <stdio.h> 
#include <stdlib.h>

struct database_node { 
    int id;
    int value;
    struct database_node* next_node; 
}; 

//Insert value to Next node and link 2 nodes to each other
static void insert_new_node(struct database_node *current_node, struct database_node *next_node, int id, int value)  {
    next_node->id = id;
    next_node->value = value;
    current_node->next_node = next_node;
}

static void display_link_list(struct database_node *first_node){
    struct database_node *ptr = first_node;

    while(ptr != NULL)
	{        
      printf("(%d,%d) ", ptr->id, ptr->value);
      ptr = ptr->next_node;
    }
    printf("\n");
}

static int insert_node_at_middle(struct database_node *first_node, int index, int id, int value){
    struct database_node *current_node = first_node;

    struct database_node ins_node;
    
    static struct database_node tmp_node; 

    int tmp_index = 0;

    ins_node.id = id;
    ins_node.value = value;

    while(current_node != NULL)
	{        
      	if (tmp_index == index) {
            tmp_node = *current_node;
            *current_node = ins_node;
            current_node->next_node = &tmp_node;
			return 1;
      	}
		current_node = current_node->next_node;
		tmp_index++;
    }
   
    return 0;
}

int main() 
{ 
    struct database_node node_0 = {1, 100};

    struct database_node node_1, node_2;
    insert_new_node(&node_0, &node_1, 2, 200);
    insert_new_node(&node_1, &node_2, 3, 300);
    insert_new_node(&node_1, &node_2, 4, 400);
    node_2.next_node = NULL; //End link list

	printf("Before updating:\n");
    display_link_list(&node_0);

    insert_node_at_middle(&node_0, 1, 123, 456);

	printf("After updating:\n");
	display_link_list(&node_0);
    return 0; 
} 
```

### Create

Create/insert a node at index 0 (node 1):

Old linked list

```
Node 1 (old node) -> Node 2 -> Node 3 -> ... -> NULL
```

New linked list

```
Node 1 (new node) -> Node 1 (inserted node/old node) -> Node 2 -> Node 3 -> ... -> NULL
```

As traversing linked list started from node 1, the inserted node is actually node 1 old node (in the diagram above), while node 1 new node just has its value updated.

So in this diagram:

* Node 1 new node has the address of node 1 old node but has latest inserted value
* Node 1 old node is a newly created node and has the value of node 1 old node

So the inserted node is a temporary node to stored the value of node 1 old node.

Check implementation for this in [insert_with_index.c](insert_with_index.c) program.

There is another way to insert a node at first index is to use double pointer, check [multiple_defines_for_insert_with_index.c](multiple_defines_for_insert_with_index.c) source code.

# Implementations

### Create

Create and read all member of a linked list: [create_and_read_linked_list.c](create_and_read_linked_list.c)

Insert a new node to an existed linked list by the specified index: [insert_with_index.c](insert_with_index.c). Function ``insert_node_at_index()`` supports inserting a new node at index 0 (beginning of the linked listed) and at the middle index. If the insert node is at index = linked list size, the linked list will appended.

### Read

**Read the whole linked list**: Check [create_and_read_linked_list.c](create_and_read_linked_list.c) source code, with function ``display_linked_list()`` to display the whole linked list. Note that ``first_node`` as parameter of ``display_linked_list()`` must be passed by reference as linked list performs traversing based on the address, which started from first node.

**Read a node at specific index**: Function ``display_by_index()``

```c
//Other operations like in create_and_read_linked_list.c
int display_by_index(struct database_node *first_node, int index){
    struct database_node *ptr = first_node;
    int tmp_index = 0;
    while(ptr != NULL)
	{
        if (tmp_index == index) {
            printf("index: %d, (%d,%d)", index, ptr->id, ptr->value);
            return 1;
        }    
        tmp_index += 1;
        ptr = ptr->next_node;
    }
	printf("There is no index %d in linked list\n", index);
    return 0;
}

int main() 
{ 
	struct database_node *node_0, *node_1, *node_2;
	node_0 = (struct database_node *)malloc(sizeof(struct database_node));

    node_0->id = 1;
    node_0->value = 100;

    node_1 = (struct database_node *)malloc(sizeof(struct database_node));
    node_2 = (struct database_node *)malloc(sizeof(struct database_node));
    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = NULL; //End link list
	display_linked_list(node_0);

    display_by_index(node_0, 0);

    return 0; 
}
```

### Update

Update node value at a specific index, then display the linked list before and after updating to see changes:

```c
//Other operations like in create_and_read_linked_list.c
int update_node_at_index(struct database_node first_node, int index, int id, int value){
    struct database_node *ptr = &first_node;
    int tmp_index = 0;

    while(ptr != NULL)
	{
        if (tmp_index == index) {
			ptr->id = id;
			ptr->value = value;
            return 1;
        }    
        tmp_index += 1;
        ptr = ptr->next_node;
    }
    return 0;
}

int main() 
{ 
    struct database_node node_0 = {1, 100};
    struct database_node node_1, node_2;
    insert_new_node(&node_0, &node_1, 2, 200);
    insert_new_node(&node_1, &node_2, 3, 300);
    node_2.next_node = NULL; //End link list

	printf("Before updating:\n");
    display_link_list(node_0);
	update_node_at_index(node_0, 1, 23, 1234);

	printf("\nAfter updating:\n");
	display_link_list(node_0);

    return 0; 
} 
```

### Delete

Delete node at specific index (at index 0, middle index and the last index):

```c
//Other operations like in create_and_read_linked_list.c
void delete_node_at_index(struct database_node *first_node, int index){
    struct database_node *current_node = first_node, *prev_node;
    prev_node = (struct database_node *)malloc(sizeof(struct database_node));
    
    int tmp_index = 0;

    if (tmp_index == index) {      
		*first_node = *(first_node->next_node);
		first_node = first_node->next_node;

        return;
    }

    while(current_node != NULL)
	{        
        if (tmp_index == index) {
            prev_node->next_node = current_node->next_node;
            return;
        }
        prev_node = current_node;  
        current_node = current_node->next_node;
        tmp_index++;
    }
   
    return;
}
//Other operations like in create_and_read_linked_list.c
```

## Examples

* Form a string by linked list from the orginal string: [string_from_singly_linked_list.c](string_from_singly_linked_list.c)
