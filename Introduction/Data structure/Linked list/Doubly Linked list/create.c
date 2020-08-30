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

void displayLinkList(){
    struct databaseNode *ptr = node0;

    while(ptr != NULL)
	{        
      printf("(%d,%d)", ptr->id, ptr->intValue);
      ptr = ptr->nextNode;
    }
    puts("");
}

void readDataFromPreviousNode(struct databaseNode *node){
    //Exception: first node
    if (node->previousNode == NULL) {
        puts("This is the first node");
        return;
    }

    //Get ID of previous node from current node
    printf("node->previousNode->id: %d \n", node->previousNode->id); 

    //Get intValue of previous node from current node
    printf("node1->previousNode->intValue: %d \n", node->previousNode->intValue);
}

void readDataFromNextNode(struct databaseNode *node){
    //Exception: End node
    if (node->nextNode == NULL) {
        puts("This is the end node");
        return;
    }
    //Get ID of next node from current node
    printf("node->nextNode->id: %d \n", node->nextNode->id); 

    //Get intValue of next node from current node
    printf("node->nextNode->intValue: %d \n", node->nextNode->intValue);
}

void readDataFromCurrentNode(struct databaseNode *node){
    //Get ID of current node
    printf("node->id: %d \n", node->id); 

    //Get intValue of current node
    printf("node1->intValue: %d \n", node->intValue);
}

int main(int argc, char *argv[])
{ 
    node0 = (struct databaseNode *)malloc(sizeof(struct databaseNode));

    struct databaseNode node1, node2;
    insertNodeValues(NULL, node0, &node1, 1, 100);
    insertNodeValues(node0, &node1, &node2, 2, 200);
    insertNodeValues(&node1, &node2, NULL, 3, 300);

    displayLinkList();

    //Read data from previous node, current node and next node to check the integrity of the link list
    readDataFromPreviousNode(node0);
    readDataFromCurrentNode(node0);
    readDataFromNextNode(node0);

    return 0; 
} 