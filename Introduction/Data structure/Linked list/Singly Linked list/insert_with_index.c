#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct database_node { 
    int id;
    int value;
    struct database_node* next_node; 
} *node_0; 

//Insert value to next_node and link 2 nodes to each other
static void insert_new_node(struct database_node *current_node, struct database_node *next_node, int id, int value)  {
    next_node->id = id;
    next_node->value = value;
    current_node->next_node = next_node;
}

void display_link_list(struct database_node first_node){
    struct database_node *ptr = &first_node;

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
int insert_node_at_middle(struct database_node *first_node, int index, int id, int value){
    struct database_node *current_node = first_node, *ins_node, *prev_node;

	ins_node = (struct database_node *)malloc(sizeof(struct database_node));
    prev_node = (struct database_node *)malloc(sizeof(struct database_node));

    int tmp_index = 0;

    ins_node->id = id;
    ins_node->value = value;

    while(current_node != NULL)
	{        
      	if (tmp_index == index) {
            prev_node->next_node = ins_node;
			ins_node->next_node = current_node;
			return 1;
      	}
        prev_node = current_node;  
		current_node = current_node->next_node;
		tmp_index++;
    }
   
    return 0;
}

int main(int argc, char *argv[]) 
{ 
    node_0 = (struct database_node *)malloc(sizeof(struct database_node));

    node_0->id = 1;
    node_0->value = 100;

    struct database_node *node_1, *node_2;
    node_1 = (struct database_node *)malloc(sizeof(struct database_node));
    node_2 = (struct database_node *)malloc(sizeof(struct database_node));

    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = NULL; //End link list

	printf("Before updating:\n");
    display_link_list(*node_0);

    insert_node_at_middle(node_0, 2, 123, 456);

    printf("After updating at index 2:\n");
    display_link_list(*node_0);

    insert_node_at_middle(node_0, 1, 789, 123);
    printf("After updating at index 1:\n");
    display_link_list(*node_0);

    return 0; 
} 