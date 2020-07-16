#include <stdio.h>
main() {
   int LA[] = {1,3,5,7,8};
   int k = 2, n = 5;
   int i = 0;
   
   printf("Result before deleting:\n");
	
   for(i = 0; i<n; i++) {
      printf("LA[%d] = %d \n", i, LA[i]);
   }
	j=k;	
   while(j<=n){
      LA[j] = LA[j+1];
      j++;
   }
 	n = n-1;
   printf("Result after deleting:\n");
	
   for(i = 0; i<n; i++) {
      printf("LA[%d] = %d \n", i, LA[i]);
   }
}