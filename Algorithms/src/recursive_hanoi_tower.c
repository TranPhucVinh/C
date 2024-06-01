#include <stdio.h>

void moveDisk(int diskNumber, int startPos, int midPos, int endPos);

int main(){
	int diskNumber;
	printf("Enter disk number: ");
	scanf("%d", &diskNumber);
	moveDisk(diskNumber, 1, 2, 3);
}

void moveDisk(int diskNumber, int startPos, int midPos, int endPos)
{
	if (diskNumber >1)
	{		// move n-1 upper disk from startPos to midPos
		moveDisk(diskNumber-1, startPos, endPos, midPos);
		//move the biggest disk from startPos to endPos
		printf("move disk number %d from column %d to column %d \n", diskNumber, startPos, endPos);
		// move n-1 upper disk from midPos to endPos
		moveDisk(diskNumber-1, midPos, startPos, endPos);
	}
	else printf("move disk number 1 from column %d to column %d \n", startPos, endPos);
}
