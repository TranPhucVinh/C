#include <stdio.h> 
#include <stdlib.h>

struct _LinkedList { 
    int value;
    struct _LinkedList* next_node; 
}; 

typedef struct _LinkedList LinkedList;

void display_link_list(LinkedList *head){
    LinkedList *ptr = head;

    while(ptr != NULL)
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

        if (i != arr_sz -1){
            current_node->next_node = next_node;
            current_node = next_node;
        } else {
            current_node->next_node = NULL;
            free(next_node);
        }
    }
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
