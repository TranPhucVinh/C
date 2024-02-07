#include <stdio.h> 
#include <stdlib.h>

struct _LinkedList { 
    int id;
    int value;
    struct _LinkedList* next_node; 
}; 

typedef struct _LinkedList LinkedList;

//Insert value to Next node and link 2 nodes to each other
void insert_new_node(LinkedList *current_node, LinkedList *next_node, int id, int value)  {
    next_node->id = id;
    next_node->value = value;
    current_node->next_node = next_node;
}

void display_link_list(LinkedList *first_node){
    LinkedList *ptr = first_node;

    while(ptr != NULL)
	{        
      printf("(%d,%d) ", ptr->id, ptr->value);
      ptr = ptr->next_node;
    }
    printf("\n");
}

int insert_node_at_middle(LinkedList *first_node, int index, int id, int value){
    int size;
    LinkedList *current_node = first_node;
    LinkedList *ins_node, *prev_node;
    
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

int main() 
{ 
    LinkedList node_0 = {1, 100};

    LinkedList node_1, node_2;
    insert_new_node(&node_0, &node_1, 2, 200);
    insert_new_node(&node_1, &node_2, 3, 300);
    insert_new_node(&node_1, &node_2, 4, 400);
    node_2.next_node = NULL; //End link list

	printf("Before updating:\n");
    display_link_list(&node_0);

    insert_node_at_middle(&node_0, 1, 123, 456);

	printf("After updating:\n");
	display_link_list(&node_0);

    insert_node_at_middle(&node_0, 0, 567, 890);
    display_link_list(&node_0);
    return 0; 
} 
