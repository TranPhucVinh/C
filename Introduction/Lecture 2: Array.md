### Enter value of array

Enter the value of each member in array then print out on screen.

The size of array is compulsory, not like array[] in JavaScript.

```c
#include <stdio.h>

main() {
	int i, n, array[100];
	printf("Enter the number of members: ");
	scanf("%d", &n);
	printf("Enter the value of each member: ");
	for (i = 0; i < n; i++){
		scanf("%d", &array[i]);
	}
	for (i=0; i < n; i++){
		printf("Value of member %d is %d \n", i, array[i]);
	}
}
```

To only print out the value of array

```c
for (i=0; i < n; i++){
		printf("%d ", array[i]);
}
```
### Adding a new number to array

```c
#include <stdio.h>
main() {
   int LA[] = {1,3,5,7,8};
   int item = 10, k = 3, n = 5;
   int i = 0, j = n;
   
   printf("Result before adding:\n");
	
   for(i = 0; i<n; i++) {
      printf("LA[%d] = %d \n", i, LA[i]);
   }
    
   n = n + 1;
	
   while( j >= k){
      LA[j+1] = LA[j];
      j = j - 1;
   }
	
   LA[k] = item;
   
   printf("Result after adding:\n");
	
   for(i = 0; i<n; i++) {
      printf("LA[%d] = %d \n", i, LA[i]);
   }
}
```

### Delete member in array

```c
#include <stdio.h>
main() {
   int LA[] = {1,3,5,7,8};
   int k = 2, n = 5;
   int i = 0;
   
   printf("Result before adding:\n");
	
   for(i = 0; i<n; i++) {
      printf("LA[%d] = %d \n", i, LA[i]);
   }
	j=k;	
   while(j<=n){
      LA[j] = LA[j+1];
      j++;
   }
 	n = n-1;
   printf("Result after adding:\n");
	
   for(i = 0; i<n; i++) {
      printf("LA[%d] = %d \n", i, LA[i]);
   }
}
```

**Result**

```
Result before adding:
LA[0] = 1 
LA[1] = 3 
LA[2] = 5 
LA[3] = 7 
LA[4] = 8 
Result after adding:
LA[0] = 1 
LA[1] = 3 
LA[2] = 7 
LA[3] = 8 
```
