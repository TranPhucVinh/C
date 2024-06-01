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

int logarit_calculation(int base, int value){
    if (base == 0) {
        printf("logarit base can't be 0\n");
        return 0;
    }
    if ((value == 1)||(value == 0)) return 0;
    return 1 + logarit_calculation(base, value/base);
}

int main(){
    printf("a %d\n", logarit_calculation(2, 1024));
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
A real life example where Fibonacci sequence appears: **Climbing stairs** (Leetcode)

Description: You are climbing a staircase. It takes **n** steps to reach the top. Each time you can either climb **1** or **2** steps. In how many distinct ways can you climb to the top?

* Input: n = 2
* Output: 2
* Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

* Input: n = 3
* Output: 3
* Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

* Input: n = 4
* Output: 5
* Explanation: There are three ways to climb to the top.
1. 1 + 1 + 1 + 1
2. 1 + 2 + 1
3. 2 + 1 + 1
4. 1 + 1 + 2
5. 2 + 2

As there are only 2 options (1 step and 2 step), so

n steps = 1 step + total way to step in (n-1) steps = 2 steps + + total way to step in (n-1) steps

* With (1, n - 1), there are (n-1) ways to walk
* With (2, n - 2), there are (n-2) ways to walk

So this will form a fibonacci sequence: total_steps[n] = total_steps[n-1] + total_steps[n-2]

# pow(x,n) implemented by recursive

For power up with big number ``n`` to avoid stack overflow, compute ``half`` as power(x, n/2):
* If n is even, return ``half * half``.
* If n is odd, return ``half * half * x``.

**Source**: [recursive_power.c](src/recursive_power.c)

# Other applications
* [Hanoi tower](src/recursive_hanoi_tower.c)
* [Raspbian device tree: Find all nodes with compatible string](https://github.com/TranPhucVinh/Raspberry-Pi-C/blob/main/Kernel/Device%20tree/find_all_nodes_with_comp_str.c)
* [Permutation](Permutation.md)
* [Combination](Combination.md)
* [Check if an index existed inside a linked list](https://github.com/TranPhucVinh/C/blob/master/Data%20structure/Linked%20list/Singly%20linked%20list/Implementations.md#read-a-node-at-specific-index)
