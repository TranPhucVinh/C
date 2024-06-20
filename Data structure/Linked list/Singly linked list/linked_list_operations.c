#include <stdio.h> 
#include <stdlib.h> 

struct _LinkedList { 
    int id;
    int value;
    struct _LinkedList* next_node; 
}; 

typedef struct _LinkedList LinkedList;

//Insert value to Next node and link 2 nodes to each other
void insert_new_node(LinkedList *current_node, LinkedList *next_node, int id, int value){
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

void delete_node_at_index(LinkedList *first_node, int index){
    LinkedList *current_node = first_node, *prev_node;
    prev_node = (LinkedList*)malloc(sizeof(LinkedList));

    // Delete the first node
    if (index == 0) {      
		*first_node = *(first_node->next_node);
		first_node = first_node->next_node;
        return;
    }

    int tmp_index = 0;

    while(current_node != NULL) {        
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

int main() 
{ 
    LinkedList *node_0, *node_1, *node_2;
	node_0 = (LinkedList *)malloc(sizeof(LinkedList));

    node_0->id = 1;
    node_0->value = 100;

    node_1 = (LinkedList *)malloc(sizeof(LinkedList));
    node_2 = (LinkedList *)malloc(sizeof(LinkedList));
    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = NULL; //End link list

    display_link_list(node_0);
    delete_node_at_index(node_0, 0);
    display_link_list(node_0);
    return 0; 
} 
