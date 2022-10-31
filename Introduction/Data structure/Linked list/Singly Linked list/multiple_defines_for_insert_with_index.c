#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct database_node { 
    int id;
    int value;
    struct database_node* next_node; 
} *node_0; 

//Insert value to next_node and link 2 nodes to each other
void insert_new_node(struct database_node *current_node, struct database_node *next_node, int id, int value)  {
    next_node->id = id;
    next_node->value = value;
    current_node->next_node = next_node;
}

void display_linked_list(struct database_node *first_node){
    struct database_node *ptr = first_node;

    while(ptr != NULL)
	{        
		printf("(%d,%d) ", ptr->id, ptr->value);
		ptr = ptr->next_node;
    }
    printf("\n");
}

#define ENABLE_INSERT_HEAD

/**
 * insert_node_at_index - Insert a new node to linked list based on the index from 0 to
 * (linked list size - 1), If index = linked list size, append linked list
 * @first_node: first_node must be pass by reference for case the inserted node is the first node
 * @index:
 * @id:
 * @value:
 */
#if defined(ENABLE_INSERT_HEAD)
int insert_node_at_index(struct database_node **first_node, int id, int value)
#else
int insert_node_at_index(struct database_node *first_node, int index, int id, int value)
#endif
{
	int size;
    struct database_node *current_node, *ins_node, *prev_node;
	ins_node = (struct database_node *)malloc(sizeof(struct database_node));
    prev_node = (struct database_node *)malloc(sizeof(struct database_node));

    int tmp_index = 0;

    ins_node->id = id;
    ins_node->value = value;
#if defined(ENABLE_INSERT_HEAD)
    ins_node->next_node = *first_node;
    *first_node = ins_node;
    return 0;
#else
    if (index == 0)
	{
		printf("Cant insert head as ENABLE_INSERT_HEAD is not defined\n");
		return -1;
	}
    current_node = first_node;
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

	size = tmp_index;
	/*
		After traverse the whole linked list and get to the last node
		with index (linked list size - 1), append the linked list 
		if index == size
	*/
	if (index == size){
		prev_node->next_node = ins_node;
		return 1;
	} 
#endif
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

	printf("Before inserting:\n");
    display_linked_list(node_0);

    // Insert node at index 0 (insert head)
    insert_node_at_index(&node_0, 12, 34);
    printf("After inserting:\n");
    display_linked_list(node_0);

    // insert_node_at_index(node_0, 1, 56, 78);
    // printf("After inserting:\n");
    // display_linked_list(node_0);

    return 0; 
} 
