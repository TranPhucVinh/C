# Use recursive to calculate the sum from 1 to n

```c
#include <stdio.h>

int sum_of_numbers(int x);

int main()
{  
	int number = 20;
	printf("Sum from 1 to %d: %d", number, sum_of_numbers(number));
}

int sum_of_numbers(int number){
	if (number == 1) return 1;
	return number + sum_of_numbers(number - 1);
}
```
# Logarit can only be calculated by recursive
```c
#include <stdio.h>

int logarit_calculation(int base, int value);

int main(){
    int logarit = logarit_calculation(2, 1024);
    printf("a %d\n", logarit);
}

int logarit_calculation(int base, int value){
    int logarit;
    if (base == 0) {
        printf("logarit base can't be 0\n");
        return 0;
    }
    if (value == 1) return 0;
    return 1 + logarit_calculation(base, value/base);
}
```
# Fibonacci sequence
Implementation of Fibonacci by recursive function for big number, like 50th, takes ten of seconds to run due to the stack grown up during the execution:
```c
long fibonacci(int n){ 
    if ((n==1)||(n==2)) return 1;
    else {
       return fibonacci(n-1) + fibonacci(n-2);
    }
}
fibonacci(50); // Take ten of seconds to run
```
Implementation of Fibonacci by using array to store all members and recursively define will take 1 second to run:
```c
long fibonacci[50];
fibonacci[0] = 1;
fibonacci[1] = 1;
for (int i = 2; i < 50; i++){
	fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
}
printf("%ld\n", fibonacci[49]);// 50th number
```    
# Other applications
* [Hanoi tower](Hanoi_tower.c)
* [Raspbian device tree: Find all nodes with compatible string](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/Device%20tree/find_all_nodes_with_comp_str.c)
* [Permutation](Permutation.md)
* [Combination](Combination.md)
* [Check if an index existed inside a linked list](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/Implementations.md#read-a-node-at-specific-index)
