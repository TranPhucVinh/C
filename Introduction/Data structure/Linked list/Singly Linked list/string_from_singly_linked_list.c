#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct characterNode { 
    char character;
    struct characterNode* nextNode; 
}; 

//Insert value to Next node and link 2 nodes to each other
void insertNodeValues(struct characterNode *currrentNode, struct characterNode *nextNode, char character)  {
    nextNode->character = character;
    currrentNode->nextNode = nextNode;
}

void formStringWithLinkList(char *_originalString, char *_displayedString){
	int index = 0;
	struct characterNode *currrentNode;

	/*
		Must allocate memory for firstNode. Without this, there will be error:
		*** stack smashing detected ***
	*/
	struct characterNode *firstNode;
	firstNode = (struct characterNode*) malloc(sizeof(struct characterNode));

	while (index < strlen(_originalString)){
		struct characterNode *nextNode;

		/*
			Must allocate memory for nextNode to keep the memory location outside function formStringWithLinkList()
		*/
		nextNode = (struct characterNode*) malloc(sizeof(struct characterNode));

		if (!index) {
			currrentNode = firstNode;
			currrentNode->character = _originalString[0];
			
		}
		insertNodeValues(currrentNode, nextNode, _originalString[index+1]);
		currrentNode = nextNode;
		index += 1;
	}
    currrentNode->nextNode = NULL; //End link list

	struct characterNode *ptr = firstNode;

	ptr = firstNode;
	index = 0;
	while(ptr != NULL)
	{        
		_displayedString[index] = ptr->character;
      	ptr = ptr->nextNode;
		index += 1;
	}
}

int main() 
{ 
	char originalString[] = "Hello, World !";
	char *displayedString;
	displayedString = (char*) malloc (100);
	formStringWithLinkList(originalString, displayedString);
	printf("%s\n", displayedString);

    return 0; 
} 