#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct databaseNode { 
    int id;
    int intValue;
    struct databaseNode* nextNode; 
    struct databaseNode* previousNode; 
} *node0; 

//Insert value to Next node and link 2 nodes to each other
void insertNodeValues(struct databaseNode *previousNode, struct databaseNode *currrentNode, struct databaseNode *nextNode, int id, int intValue)  {
    currrentNode->id = id;
    currrentNode->intValue = intValue;
    currrentNode->previousNode = previousNode;
    currrentNode->nextNode = nextNode;
}

int insertNodeValuesAtIndex(int index, int id, int intValue){
    struct databaseNode *currentPtr = node0, *insertNode, *previousPtr;

	insertNode = (struct databaseNode *)malloc(sizeof(struct databaseNode));
    previousPtr = (struct databaseNode *)malloc(sizeof(struct databaseNode));

    int tempIndex = 0;

    insertNode->id = id;
    insertNode->intValue = intValue;

    if (tempIndex == index) {      
        insertNode->nextNode = node0;
        insertNode->previousNode = NULL;
		node0 = insertNode;
        return 1;
    }

    while(currentPtr != NULL)
	{        
      	if (tempIndex == index) {
            previousPtr->nextNode = insertNode;
            insertNode->previousNode = previousPtr;
			insertNode->nextNode = currentPtr;
			return 1;
      	}
        previousPtr = currentPtr;  
		currentPtr = currentPtr->nextNode;
		tempIndex++;
    }
   
    return 0;
}

void displayLinkList(){
    struct databaseNode *ptr = node0;

    while(ptr != NULL)
	{        
      printf("(%d,%d)", ptr->id, ptr->intValue);
      ptr = ptr->nextNode;
    }
    puts("");
}

void readDataFromPreviousNode(int searchIndex){
    struct databaseNode *currentPtr = node0;
    int tempIndex = 0;

    while(currentPtr != NULL)
	{        
      	if (tempIndex == searchIndex) {
            if (currentPtr->previousNode == NULL) {
                puts("This is the first node");
                return;
            } else {
                //Get ID of previous node from current node
                printf("node->previousNode->id: %d \n", currentPtr->previousNode->id); 

                //Get intValue of previous node from current node
                printf("node->previousNode->intValue: %d \n", currentPtr->previousNode->intValue);
                return;
            }
      	}
		currentPtr = currentPtr->nextNode;
		tempIndex++;
    }
    printf("Can't find the node at index=%d\n", searchIndex);   
}

void readDataFromNextNode(int searchIndex){
    struct databaseNode *currentPtr = node0;
    int tempIndex = 0;

    while(currentPtr != NULL)
	{        
      	if (tempIndex == searchIndex) {
            if (currentPtr->nextNode == NULL) {
                puts("This is the end node");
                return;
            } else {  
                //Get ID of next node from current node
                printf("node->nextNode->id: %d \n", currentPtr->nextNode->id); 

                //Get intValue of next node from current node
                printf("node->nextNode->intValue: %d \n", currentPtr->nextNode->intValue);
                return;
            }
      	}
		currentPtr = currentPtr->nextNode;
		tempIndex++;
    }  
    printf("Can't find the node at index=%d\n", searchIndex);
}

void readDataFromCurrentNode(int searchIndex){
    struct databaseNode *currentPtr = node0;
    int tempIndex = 0;

    while(currentPtr != NULL)
	{        
      	if (tempIndex == searchIndex) {
            //Get ID of current node
            printf("node->id: %d \n", currentPtr->id); 

            //Get intValue of current node
            printf("node->intValue: %d \n", currentPtr->intValue);
            return;
      	}
		currentPtr = currentPtr->nextNode;
		tempIndex++;
    }  
    printf("Can't find the node at index=%d\n", searchIndex);
}

int main(int argc, char *argv[])
{ 
    int index, id, intValue, searchIndex;
    char *splitString;
    long ret;

    if (argc==5){
        ret = strtol(argv[1], &splitString, 10);

        if (!strlen(splitString)) {
            index = ret;
        }  else {
            puts("You have entered the invalid index value");
            return 0;            
        }

        ret = strtol(argv[2], &splitString, 10);
        if (!strlen(splitString)) {
            id = ret;
        }  else {
            puts("You have entered the invalid id value for node");
            return 0;            
        }

        ret = strtol(argv[3], &splitString, 10);
        if (!strlen(splitString)) {
            intValue = ret;
        }  else {
            puts("You have entered the invalid integer value for node");
            return 0;            
        }

        ret = strtol(argv[4], &splitString, 10);
        if (!strlen(splitString)) {
            searchIndex = ret;
        }  else {
            puts("You have entered the invalid value for index node to check linked list integrity");
            return 0;            
        }

    } else {
        puts("You haven't entered enough parameter to execute");  
        return 0;
    }

    node0 = (struct databaseNode *)malloc(sizeof(struct databaseNode));

    struct databaseNode node1, node2;
    insertNodeValues(NULL, node0, &node1, 1, 100);
    insertNodeValues(node0, &node1, &node2, 2, 200);
    insertNodeValues(&node1, &node2, NULL, 3, 300);

    puts("Link list before insert");
    displayLinkList();

    if(insertNodeValuesAtIndex(index, id, intValue)){
        puts("\nLink list after insert");
    	displayLinkList();
    } else {
        printf("\nCan't find the node at index=%d\n", index);
    }

    puts("Check doubly linked list integrity");
    //Read data from previous node, current node and next node to check the connection of the link list
    readDataFromPreviousNode(searchIndex);
    readDataFromCurrentNode(searchIndex);
    readDataFromNextNode(searchIndex);

    return 0; 
} 