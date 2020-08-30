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

int updateNodeAtIndex(int index, int idChange, int intValueChange){
    struct databaseNode *ptr = node0;
    int tempIndex = 0;

    while(ptr != NULL)
	{
        if (tempIndex == index) {
			ptr->id = idChange;
			ptr->intValue = intValueChange;
            return 1;
        }    
        tempIndex++;
        ptr = ptr->nextNode;
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
    int updateIndex, id, intValue;
    char *splitString;
    long ret;

    if (argc==4){
        ret = strtol(argv[1], &splitString, 10);

        if (!strlen(splitString)) {
            updateIndex = ret;
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

	puts("Link list before update");
	displayLinkList();
    if(updateNodeAtIndex(updateIndex, id, intValue)){
        puts("\nLink list after update");
    	displayLinkList();
    } else {
            printf("Can't find the node at index=%d", updateIndex);
    }
    return 0; 
} 