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

int readNodeAtIndex(int index){
    struct databaseNode *ptr = node0;
    int tempIndex = 0;
    while(ptr != NULL)
	{
        if (tempIndex == index) {
            printf("index: %d, (%d,%d)", index, ptr->id, ptr->intValue);
            return 1;
        }    
        tempIndex++;
        ptr = ptr->nextNode;
    }
    return 0;
}

int main(int argc, char *argv[])
{ 
    int readIndex;
    char *splitString;
    long ret;

    if (argc==2){
        ret = strtol(argv[1], &splitString, 10);

        if (!strlen(splitString)) {
            readIndex = ret;
        }  else {
            puts("You have entered the invalid index value");
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

    if(readNodeAtIndex(readIndex)) return 0;
	else printf("Can't find the node at index=%d", readIndex);    
    return 0; 
} 