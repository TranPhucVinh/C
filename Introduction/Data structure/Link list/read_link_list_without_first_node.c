#include <stdio.h> 
#include <stdlib.h>

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

int main() 
{ 
    node0 = (struct databaseNode *)malloc(sizeof(struct databaseNode));

    node0->id = 1;
    node0->intValue = 100;
    struct databaseNode node1, node2;
    insertNodeValues(node0, &node1, 2, 200);
    insertNodeValues(&node1, &node2, 3, 300);
    node2.nextNode = NULL; //End link list

    displayLinkList();

    return 0; 
} 