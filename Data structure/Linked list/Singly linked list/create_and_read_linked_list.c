#include <stdio.h> 
#include <stdlib.h> 

struct database_node { 
    int id;
    int value;
    struct database_node* next_node; 
}; 

//Insert value to Next node and link 2 nodes to each other
void insert_new_node(struct database_node *current_node, struct database_node *next_node, int id, int value){
    next_node->id = id;
    next_node->value = value;
    current_node->next_node = next_node;
}

void display_link_list(struct database_node *first_node){
    struct database_node *ptr = first_node;

    while(ptr != NULL)
	{        
		printf("(%d,%d) ", ptr->id, ptr->value);
		ptr = ptr->next_node;
    }
	printf("\n");
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

    display_link_list(node_0);

    return 0; 
} 
