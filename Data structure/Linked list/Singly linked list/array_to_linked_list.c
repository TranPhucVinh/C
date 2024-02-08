#include <stdio.h> 
#include <stdlib.h>

struct _LinkedList { 
    int value;
    struct _LinkedList* next_node; 
}; 

typedef struct _LinkedList LinkedList;

void display_link_list(LinkedList *head){
    LinkedList *ptr = head;

    while(ptr->next_node != NULL)
	{        
      printf("(%d) ", ptr->value);
      ptr = ptr->next_node;
    }
    printf("\n");
}

LinkedList *array_to_linked_list(int *array, int arr_sz){
    LinkedList *head = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *current_node = head;

    for (int i = 0; i < arr_sz; i++){
        LinkedList *next_node = (LinkedList *)malloc(sizeof(LinkedList));
        current_node->value = array[i];
        current_node->next_node = next_node;
        current_node = next_node;
        printf("array[%d] %d ", i, array[i]);
    }
    // current_node->next_node = NULL;
    current_node = NULL;
    printf("\n");
    return head;
}

int main() 
{ 
    int arr[5] = {1, 2, 3, 4, 5};
    // int arr[1] = {1};
    
    LinkedList *head = array_to_linked_list(arr, 5);
    display_link_list(head);

    return 0; 
}
