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

void display_link_list(struct database_node *first_node, int size){
    int index = 0;
    struct database_node *ptr = first_node;

    while(index < size)
	{        
		printf("(%d,%d) ", ptr->id, ptr->value);
		ptr = ptr->next_node;
        index += 1;
    }
	printf("\n");
}

void verify_circular_linked_list(struct database_node *first_node){
    /*
        * slow pointer moves one step at a time 
        * fast pointer moves two steps at a time 
    */
    struct database_node *slow, *fast;
    int jump = 0;
    
    slow = first_node;
    fast = first_node;

    while ((slow->next_node) && (slow->next_node->next_node)){
        slow = slow->next_node;
        fast = fast->next_node->next_node;
        jump += 1;
        if (slow == fast) {
            printf("This is a circular linked list, traverse poiner has to jump %d times to verify\n", jump);
            return;
        }
    }
    printf("This is a singly linked list\n");
}

int main() { 
    // Create a circular linked list then verify if it's a circular linked list
	struct database_node *node_0, *node_1, *node_2;
	node_0 = (struct database_node *)malloc(sizeof(struct database_node));

    node_0->id = 1;
    node_0->value = 100;

    node_1 = (struct database_node *)malloc(sizeof(struct database_node));
    node_2 = (struct database_node *)malloc(sizeof(struct database_node));
    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = node_0; //End link list by pointing back to node0

    display_link_list(node_0, 3);
    verify_circular_linked_list(node_0);

    // Create a singly linked list then verify if it's a circular linked list
    struct database_node *node_3, *node_4, *node_5;
	node_3 = (struct database_node *)malloc(sizeof(struct database_node));
    node_4 = (struct database_node *)malloc(sizeof(struct database_node));
    node_5 = (struct database_node *)malloc(sizeof(struct database_node));

    node_3->id = 1;
    node_3->value = 100;

    insert_new_node(node_3, node_4, 2, 200);
    insert_new_node(node_4, node_5, 3, 300);
    node_5->next_node = NULL;

    display_link_list(node_3, 3);
    verify_circular_linked_list(node_3);
    return 0; 
} 
