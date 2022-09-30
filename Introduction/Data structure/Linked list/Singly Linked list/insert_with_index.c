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

static void display_link_list(struct database_node first_node){
    struct database_node *ptr = &first_node;
	// struct database_node *ptr = node_0;

    while(ptr != NULL)
	{        
      printf("(%d,%d) ", ptr->id, ptr->value);
      ptr = ptr->next_node;
    }
    printf("\n");
}

/**
 * insert_node_at_middle - Insert a new node in the middle of the linked list based on the index (not at index 0 
 * and at the end of the linked list
 * @first_node: first_node must be pass by reference for case the inserted node is the first node
 * @index:
 * @id:
 * @value:
 */
static int insert_node_at_middle(struct database_node *first_node, int index, int id, int value){
	// struct database_node *current_node = &node_0;
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
    node_2.next_node = NULL; //End link list

	printf("Before updating:\n");
    display_link_list(node_0);

    insert_node_at_middle(&node_0, 1, 123, 456);

	printf("Before updating:\n");
	display_link_list(node_0);

    return 0; 
} 