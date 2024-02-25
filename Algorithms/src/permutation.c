#include <stdio.h>
#include <string.h>

#define START_PERMUTE 0
int member = 0;

void swap(char *str_arr, int x, int y)
{
	char temp = str_arr[x];
	str_arr[x] = str_arr[y];
	str_arr[y] = temp;
}
 
/*
	@cid: current ID
*/
void permute(char *str_arr, int cid)
{
	if (cid == strlen(str_arr) - 1)
	{
		member += 1;
		printf("%s\n", str_arr);
		return;
	}
	for (int i = cid; i < strlen(str_arr); i++){
		swap(str_arr, i, cid);
		permute(str_arr, cid+1);
		swap(str_arr, i, cid);//Swap to switch back to the original string
	}
}

int main()
{
    char str[] = "1234";
    permute(str, START_PERMUTE);
	printf("Total members: %d\n", member);
    return 0;
}