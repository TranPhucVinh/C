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
# Other applications
* [Hanoi tower](Hanoi_tower.c)
* [Raspbian device tree: Find all nodes with compatible string](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/Device%20tree/find_all_nodes_with_comp_str.c)
* [Permutation](Permutation.md)
* [Combination](Combination.md)
* [Check if an index existed inside a linked list](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/Implementations.md#read-a-node-at-specific-index)