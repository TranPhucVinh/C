#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_LIMIT 2147483647

//As calculation to max int number will exceed the max int value so use unsigned long int
unsigned long int calculation(int n){
	long int sum = 0;
	for (int i = 0; i <= n; i++){
		sum += i;
	}
	return sum;
}

int main(int argc, char *argv[]) {
	if (argc == 1) printf("User haven't entered number n\n");
	else if (argc == 2) {
		int n = atoi(argv[1]);
		if ((n>0) && (n<NUMBER_LIMIT)) {

			//Handle case string include number + characters/symbols, e.g: 123abc
			char *temp_string_number;
			temp_string_number = (char*) malloc(10*sizeof(char));
			sprintf(temp_string_number, "%d", n);
			int str_size = strlen(argv[1]);
			if (str_size == strlen(temp_string_number))	printf("sum from 0 to %d: %lu\n", n, calculation(n));
			else printf("Entered number include invalid string or symbol: %s\n", argv[1]);
		} else if (n >= NUMBER_LIMIT) printf("Program doesn't support calculation with number > limit number\n");
		else if (n < 0) printf("User has entered negative number: %s\n", argv[1]);	
		else printf("User has entered invalid number: %s\n", argv[1]);
	} else {
		printf("Too arguments for ./a.out while program expected only 1 argument\n");
	}
}