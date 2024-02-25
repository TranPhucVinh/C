#include <stdio.h>
#include <math.h>

int n;
int number;
int possible_results = 0;

int checkInteger(float floatNum);

int main(int argc, char *argv[])  {
	printf("Entered n: ");
	scanf("%d", &n);
	for (int i = 1; i < ((1 - sqrt(1+8*n))/-2); i++){
		float a = (float)n/((float)i + 1) - (float)i/2;
		if (checkInteger(a) != -1){
			int intNum = checkInteger(a);
			printf("All numbers are:");
			for (int j = 0; j <= i; j++) printf("%d, ", intNum+j);
			printf("\n");
			possible_results += 1;
		}
	}
	if (!possible_results) printf("Given number %d is not the sum of any consecutive numbers\n", n);
}

int checkInteger(float floatNum){
    int intNum = floatNum;

    float remainder = floatNum - intNum;

    if (remainder > 0) {
        return -1;//If not int number, return -1
    }
    return intNum;
}