#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 2147483646//total execution: 3 seconds

struct calculate_range{
	int lower_range;
	int upper_range;
};

//As calculation to max int number will exceed the max int value so use unsigned long int
unsigned long calculation(int _lower_range, int _upper_range){
	unsigned long sum = 0;
	for (int i = _lower_range; i <= _upper_range; i++){
		sum += i;
	}
	return sum;
}

void *calculation_thread(void *ptr);

int main()
{  
	pthread_t thread_1, thread_2;
	unsigned long *thread_1_return, *thread_2_return;
	struct calculate_range range_1, range_2;

	range_1.lower_range = 0;
	range_1.upper_range = N/2;

	range_2.lower_range = N/2 + 1;
	range_2.upper_range = N;

	pthread_create(&thread_1, NULL, calculation_thread, &range_1);
	pthread_create(&thread_2, NULL, calculation_thread, &range_2);

	pthread_join(thread_1, (void**)&thread_1_return);
	pthread_join(thread_2, (void**)&thread_2_return);

	unsigned long sum = *thread_1_return + *thread_2_return;
	printf("thread_1 finish executing: %lu\n", sum);
}

void *calculation_thread(void *ptr){
	struct calculate_range temp_object = *(struct calculate_range*) ptr;
	unsigned long *return_value = (unsigned long*) malloc (sizeof(unsigned long));
	*return_value = calculation(temp_object.lower_range, temp_object.upper_range);
	return return_value;
}