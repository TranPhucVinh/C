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

int insertNodeValuesAtIndex(int index, int id, int intValue){
    struct databaseNode *currentPtr = node0, *insertNode, *previousPtr;

	insertNode = (struct databaseNode *)malloc(sizeof(struct databaseNode));
    previousPtr = (struct databaseNode *)malloc(sizeof(struct databaseNode));

    int tempIndex = 0;

    insertNode->id = id;
    insertNode->intValue = intValue;

    if (tempIndex == index) {      
        insertNode->nextNode = node0;
		node0 = insertNode;
        return 1;
    }

    while(currentPtr != NULL)
	{        
      	if (tempIndex == index) {
            previousPtr->nextNode = insertNode;
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
}

int main(int argc, char *argv[]) 
{ 
	int index, id, intValue;
    char *splitString;
    long ret;

    if (argc==4){
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

    } else {
        puts("You haven't entered enough parameter to execute");  
        return 0;
    }

    node0 = (struct databaseNode *)malloc(sizeof(struct databaseNode));

    node0->id = 1;
    node0->intValue = 100;

    struct databaseNode node1, node2;
    insertNodeValues(node0, &node1, 2, 200);
    insertNodeValues(&node1, &node2, 3, 300);
    node2.nextNode = NULL; //End link list

	puts("Link list before insert");
    displayLinkList();

	if(insertNodeValuesAtIndex(index, id, intValue)){
        puts("\nLink list after insert");
    	displayLinkList();
    } else {
            printf("\nCan't find the node at index=%d", index);
    }

    
    return 0; 
} 