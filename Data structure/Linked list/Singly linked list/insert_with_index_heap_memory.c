#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct _LinkedList { 
    int id;
    int value;
    struct _LinkedList* next_node; 
} *node_0; 

typedef struct _LinkedList LinkedList;

//Insert value to next_node and link 2 nodes to each other
void insert_new_node(LinkedList *current_node, LinkedList *next_node, int id, int value)  {
    next_node->id = id;
    next_node->value = value;
    current_node->next_node = next_node;
}

void display_linked_list(LinkedList *first_node){
    LinkedList *ptr = first_node;

    while(ptr != NULL)
	{        
		printf("(%d,%d) ", ptr->id, ptr->value);
		ptr = ptr->next_node;
    }
    printf("\n");
}

/**
 * insert_node_at_index - Insert a new node to linked list based on the index from 0 to
 * (linked list size - 1), If index = linked list size, append linked list
 * @first_node: first_node must be pass by reference for case the inserted node is the first node
 * @index:
 * @id:
 * @value:
 */
int insert_node_at_index(LinkedList *first_node, int index, int id, int value){
	int size;
    LinkedList *current_node = first_node, *ins_node, *prev_node;

	ins_node = (LinkedList *)malloc(sizeof(LinkedList));
    prev_node = (LinkedList *)malloc(sizeof(LinkedList));

    int tmp_index = 0;

    ins_node->id = id;
    ins_node->value = value;

	if (tmp_index == index){
		*ins_node = *first_node;

		first_node->id = id;
		first_node->value = value;
		first_node->next_node = ins_node;
		return 1;
	}

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
   
    return 0;
}

int main(int argc, char *argv[]) 
{ 
    node_0 = (LinkedList *)malloc(sizeof(LinkedList));

    node_0->id = 1;
    node_0->value = 100;

    LinkedList *node_1, *node_2;
    node_1 = (LinkedList *)malloc(sizeof(LinkedList));
    node_2 = (LinkedList *)malloc(sizeof(LinkedList));

    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = NULL; //End link list

	printf("Before inserting:\n");
    display_linked_list(node_0);

	insert_node_at_index(node_0, 1, 123, 456);
	printf("After inserting:\n");
    display_linked_list(node_0);

    free(node_0);
    free(node_1);
    free(node_2);
    return 0; 
} 
