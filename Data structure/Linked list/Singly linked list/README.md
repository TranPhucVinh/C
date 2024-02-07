# Structure of a Singly Linked list data structure

```
Node 1 -> Node 2 -> Node 3 -> ... -> NULL
```

For memory storage reason, linked list must be implemented on heap memory.

# [Implementations](Implementations.md)

* [Create](Implementations.md#create): Create and read all member of a linked list, insert a new node to an existed linked list by the specified index
* [Read](Implementations.md#read): [Read the whole linked list](), [read a node at specific index](), get linked list size, get the middle member of the linked list by 1 time traversing
* [Update](Implementations.md#update): Update node value at a specific index
* [Delete](Implementations.md#delete): Delete node at specific index (at index 0, middle index and the last index)

# Why can't use linked list in stack memory

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

# Examples

* Form a string by linked list from the orginal string: [string_from_singly_linked_list.c](string_from_singly_linked_list.c)
