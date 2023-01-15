#include <stdio.h> 
#include <stdlib.h>

struct database_node { 
    int id;
    int value;
    struct database_node* next_node; 
    struct database_node* previous_node; 
}; 

//Insert value to Next node and link 2 nodes to each other
void insert_new_node(struct database_node *previous_node, struct database_node *current_node, struct database_node *next_node, int id, int value){
    current_node->id = id;
    current_node->value = value;
    current_node->previous_node = previous_node;
    current_node->next_node = next_node;
}

void insert_node_at_index(struct database_node *first_node, int index, int id, int value){
	int size;
    struct database_node *current_node = first_node, *ins_node, *prev_node;

	ins_node = (struct database_node *)malloc(sizeof(struct database_node));
    prev_node = (struct database_node *)malloc(sizeof(struct database_node));

    int tmp_index = 0;

    ins_node->id = id;
    ins_node->value = value;

	if (index == 0) {
		printf("Can't insert at index 0 as NULL pointer\n");
		return;
	}
	
    if (index == 1) {     
		*ins_node = *first_node;
		
		first_node->id = id;
		first_node->value = value;
		first_node->next_node->previous_node = ins_node;
		first_node->next_node = ins_node;
		ins_node->previous_node = first_node;
        return;
    }

	tmp_index += 1;//As index 0 is NULL, so increase tmp_index by 1
    while(current_node != NULL)
	{        
      	if (tmp_index == index) {
            prev_node->next_node = ins_node;
            ins_node->previous_node = prev_node;
			ins_node->next_node = current_node;
			current_node->previous_node = ins_node;
			return;
      	}
        prev_node = current_node;  
		current_node = current_node->next_node;
		tmp_index += 1;
    }

	size = tmp_index;
	if (index == size) {
		printf("Can't insert at index %d as NULL pointer\n", tmp_index);
		return;
	}

    return;
}

void display_linked_list(struct database_node *first_node){
    struct database_node *ptr = first_node;

	printf("(NULL)");
    while(ptr != NULL)
	{        
        printf("(%d,%d)", ptr->id, ptr->value);
        ptr = ptr->next_node;
    }
	printf("(NULL)\n");
}

void read_previous_node_data(struct database_node *node){
    //Exception: first node
    if (node->previous_node == NULL) {
        printf("This is the first node\n");
        return;
    }

    //Get ID of previous node from current node
    printf("node->previous_node->id: %d \n", node->previous_node->id); 

    //Get value of previous node from current node
    printf("node->previous_node->value: %d \n", node->previous_node->value);
}

void read_next_node_data(struct database_node *node){
    //Exception: End node
    if (node->next_node == NULL) {
        puts("This is the end node");
        return;
    }
    //Get ID of next node from current node
    printf("node->next_node->id: %d\n", node->next_node->id); 

    //Get value of next node from current node
    printf("node->next_node->value: %d\n", node->next_node->value);
}

void read_current_node_data(struct database_node *node){
    //Get ID of current node
    printf("node->id: %d \n", node->id); 

    //Get value of current node
    printf("node->value: %d \n", node->value);
}

int main(int argc, char *argv[])
{ 
	struct database_node *node_0 = (struct database_node *)malloc(sizeof(struct database_node));
    struct database_node *node_1 = (struct database_node *)malloc(sizeof(struct database_node));
	struct database_node *node_2 = (struct database_node *)malloc(sizeof(struct database_node));

    insert_new_node(NULL, node_0, node_1, 1, 100);
    insert_new_node(node_0, node_1, node_2, 2, 200);
    insert_new_node(node_1, node_2, NULL, 3, 300);

	printf("Before inserting:\n");
    display_linked_list(node_0);

    //Read data from previous node, current node and next node to check the integrity of the link list
    read_previous_node_data(node_1);
    read_current_node_data(node_1);
    read_next_node_data(node_1);

	insert_node_at_index(node_0, 4, 12, 34);
	printf("After inserting:\n");
	display_linked_list(node_0);

    //Read data from previous node, current node and next node to check the integrity of the link list
    read_previous_node_data(node_1);
    read_current_node_data(node_1);
    read_next_node_data(node_1);

    return 0; 
} 
