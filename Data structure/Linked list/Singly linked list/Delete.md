# Delete node at specific index (at index 0, middle index and the last index)

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
