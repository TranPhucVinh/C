// Update node value at a specific index, then display the linked list before and after updating to see changes
// Other operations like in create_and_read_linked_list.c

int update_node_at_index(struct database_node *first_node, int index, int id, int value){
    struct database_node *ptr = first_node;
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
	struct database_node *node_0, *node_1, *node_2;
	node_0 = (struct database_node *)malloc(sizeof(struct database_node));

    node_0->id = 1;
    node_0->value = 100;

    node_1 = (struct database_node *)malloc(sizeof(struct database_node));
    node_2 = (struct database_node *)malloc(sizeof(struct database_node));
    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = NULL; //End link list

	printf("Before updating:\n");
	display_linked_list(node_0);

	update_node_at_index(node_0, 1, 23, 1234);

	printf("\nAfter updating:\n");
	display_linked_list(node_0);

    return 0; 
} 
```
