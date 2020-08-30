#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct databaseNode { 
    int id;
    int intValue;
    struct databaseNode* nextNode; 
} *node0; 

//Insert value to Next node and link 2 nodes to each other
void insertNodeValues(struct databaseNode *currrentNode, struct databaseNode *nextNode, int id, int intValue)  {
    nextNode->id = id;
    nextNode->intValue = intValue;
    currrentNode->nextNode = nextNode;
}

void displayLinkList(){
    struct databaseNode *ptr = node0;

    while(ptr != NULL)
	{        
      printf("(%d,%d)", ptr->id, ptr->intValue);
      ptr = ptr->nextNode;
    }
}

int deleteNodeAtIndex(int index){
    struct databaseNode *currentPtr = node0, *previousPtr;
    previousPtr = (struct databaseNode *)malloc(sizeof(struct databaseNode));
    
    int tempIndex = 0;

    if (tempIndex == index) {      
        node0 = node0->nextNode;
        return 1;
    }

    while(currentPtr != NULL)
	{        
        if (tempIndex == index) {
            previousPtr->nextNode = currentPtr->nextNode;
            return 1;
        }
        previousPtr = currentPtr;  
        currentPtr = currentPtr->nextNode;
        tempIndex++;
    }
   
    return 0;
}

int main(int argc, char *argv[])
{ 
    int deleteIndex;
    char *splitString;
    long ret;

    if (argc > 1){
        ret = strtol(argv[1], &splitString, 10);
        if (!strlen(splitString)) {
            deleteIndex = ret;
        }  else {
            puts("You have entered the invalid index value");
            return 0;            
        }
    } else {
        puts("You haven't entered the delete index");  
        return 0;
    }
    node0 = (struct databaseNode *)malloc(sizeof(struct databaseNode));

    node0->id = 1;
    node0->intValue = 100;
    
    struct databaseNode node1, node2;
    insertNodeValues(node0, &node1, 2, 200);
    insertNodeValues(&node1, &node2, 3, 300);
    node2.nextNode = NULL; //End link list

	puts("Link list before delete");
	displayLinkList();
    if (deleteNodeAtIndex(deleteIndex)){
        puts("\nLink list after update");
    	displayLinkList();
        return 0; 
    } else {
        printf("\nCan't find the node at index=%d", deleteIndex);
    }
} 