#include <stdio.h> 
#include <stdlib.h> 

struct _LinkedList { 
    int value;
    struct _LinkedList* next_node; 
}; 

typedef struct _LinkedList LinkedList;

//Insert value to Next node and link 2 nodes to each other
void insert_new_node(LinkedList *current_node, LinkedList *next_node, int value){
    next_node->value = value;
    current_node->next_node = next_node;
}

void linked_list_to_array(LinkedList *first_node){
    LinkedList *ptr = first_node;
    int arr_sz = 0;

    // Find array length
    while(ptr != NULL)
	{        
		ptr = ptr->next_node;
        arr_sz += 1;
    }

    int *array = (int*) malloc(sizeof(int)*arr_sz);

    int index = 0;

    ptr = first_node; // Reset pointer to first_node

    // Set value for array
    while(ptr != NULL)
	{    
        array[index++] = ptr->value;
		ptr = ptr->next_node;
    }

    for (int i = 0; i < arr_sz; i++){
        printf("%d ", array[i]);
    }

	printf("\n");
}

int main() 
{ 
    LinkedList *node_0, *node_1, *node_2;
	node_0 = (LinkedList *)malloc(sizeof(LinkedList));

    node_0->value = 1;

    node_1 = (LinkedList *)malloc(sizeof(LinkedList));
    node_2 = (LinkedList *)malloc(sizeof(LinkedList));
    insert_new_node(node_0, node_1, 2);
    insert_new_node(node_1, node_2, 3);
    node_2->next_node = NULL; //End link list

    linked_list_to_array(node_0);

    return 0; 
} 