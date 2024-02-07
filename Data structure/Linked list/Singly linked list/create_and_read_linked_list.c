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

    return 0; 
} 
