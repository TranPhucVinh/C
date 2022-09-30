## Operations

### Structure of a Singly Linked list data structure

```
Node 1 -> Node 2 -> Node 3 -> ... -> NULL
```

### Create

Create and read all member of a linked list: [create_and_read_linked_list.c](create_and_read_linked_list.c)

Insert a new node to an existed linked list by the specified index: [insert_with_index.c](insert_with_index.c)

### Read

Read a node at specific index

```c
//Other operations like in create_and_read_linked_list.c
int read_member(struct database_node first_node, int index){
    struct database_node *ptr = &first_node;
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
    return 0;
}

int main() 
{ 
    struct database_node node_0 = {1, 100};
    struct database_node node_1, node_2;
    insert_new_node(&node_0, &node_1, 2, 200);
    insert_new_node(&node_1, &node_2, 3, 300);
    node_2.next_node = NULL; //End link list

    read_member(node_0, 2);

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

Delete node at specific index: [delete_node_with_index.c](delete_node_with_index.c)

Argument when executing: 

* ``Argument 1``: Index to delete

## Examples

* Form a string by linked list from the orginal string: [string_from_singly_linked_list.c](string_from_singly_linked_list.c)
