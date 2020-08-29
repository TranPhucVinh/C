#include <stdio.h> 
  
struct databaseNode { 
    int id;
    int intValue;
    struct databaseNode* nextNode; 
}; 

//Insert value to Next node and link 2 nodes to each other
void insertNodeValues(struct databaseNode *currrentNode, struct databaseNode *nextNode, int id, int intValue)  {
    nextNode->id = id;
    nextNode->intValue = intValue;
    currrentNode->nextNode = nextNode;
}

void readNodeAtIndex(struct databaseNode *firstNode, int index){
    struct databaseNode *ptr = firstNode;
    int tempIndex = 0;
    while(ptr != NULL)
	{
        if (tempIndex == index) {
            printf("index: %d, (%d,%d)", index, ptr->id, ptr->intValue);
            return;
        }    
        tempIndex++;
        ptr = ptr->nextNode;
    }
    printf("Can't find the node at index=%d", index);
}

int main() 
{ 
    struct databaseNode node0 = {1, 100};
    struct databaseNode node1, node2;
    insertNodeValues(&node0, &node1, 2, 200);
    insertNodeValues(&node1, &node2, 3, 300);
    node2.nextNode = NULL; //End link list

    readNodeAtIndex(&node0, 2);

    return 0; 
} 