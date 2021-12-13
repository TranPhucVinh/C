#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct characterNode { 
    char character;
    struct characterNode* nextNode; 
}; 

int readNodeAtIndex(int index,  struct characterNode *firstNode);

void displayLinkList(struct characterNode *firstNode){
    struct characterNode *ptr = firstNode;

    while(ptr != NULL)
	{        
      printf("%c", ptr->character);
      ptr = ptr->nextNode;
    }
}


//Insert value to Next node and link 2 nodes to each other
void insertNodeValues(struct characterNode *currrentNode, struct characterNode *nextNode, char character)  {
    nextNode->character = character;
    currrentNode->nextNode = nextNode;
}

void formStringWithLinkList(struct characterNode *firstNode, char *_originalString, char *_displayedString){
	int index = 0;
	struct characterNode *currrentNode;
	firstNode = (struct characterNode*) malloc(sizeof(struct characterNode));

	while (index < strlen(_originalString)){
		struct characterNode *nextNode;
		nextNode = (struct characterNode*) malloc(sizeof(struct characterNode));

		if (!index) {
			currrentNode = firstNode;
			currrentNode->character = _originalString[0];
			
		}
		insertNodeValues(currrentNode, nextNode, _originalString[index+1]);
		currrentNode = nextNode;
		index += 1;
		// printf("next node: %c\n", nextNode->character);
	}
    currrentNode->nextNode = NULL; //End link list

	displayLinkList(firstNode);
	// readNodeAtIndex(2, firstNode);

	// struct characterNode *ptr = firstNode;
	
	// int string_length;
	// //Get length of link list database to allocate the string char pointer with length
	// while(ptr != NULL)
	// {        
	// 	string_length += 1;
	// 	ptr = ptr->nextNode;
	// }

	// printf("String length %d\n", string_length);
	// _displayedString = (char*) malloc(10);

	// ptr = firstNode;
	// index = 0;
	// while(ptr != NULL)
	// {        
	// 	_displayedString[index] = ptr->character;
    //   	ptr = ptr->nextNode;
	// }
}

int readNodeAtIndex(int index, struct characterNode *firstNode){
    struct characterNode *ptr = firstNode;
    int tempIndex = 0;
    while(ptr != NULL)
	{
        if (tempIndex == index) {
            printf("index: %d, %c", index, ptr->character);
            return 1;
        }    
        tempIndex++;
        ptr = ptr->nextNode;
    }
    return 0;
}

int main() 
{ 
	char originalString[] = "Hello, World !";
	char *displayedString;

    struct characterNode *firstNode;

	formStringWithLinkList(firstNode, originalString, displayedString);

	// int index = 0;
	// struct characterNode *currrentNode;

	// while (index < sizeof(originalString)){
	// 	struct characterNode *nextNode;
	// 	if (!index) {
	// 		firstNode->character = originalString[0];
	// 		currrentNode = firstNode;
	// 	}
	// 	insertNodeValues(currrentNode, nextNode, originalString[index+1]);
	// 	currrentNode = nextNode;
	// 	index += 1;
	// 	printf("next node: %c\n", nextNode->character);
	// }
    // currrentNode->nextNode = NULL; //End link list

	// displayLinkList(firstNode);

	// printf("%s\n", displayedString);

    return 0; 
} 
