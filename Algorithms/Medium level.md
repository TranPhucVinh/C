# Find if a given number is the sum of consecutive numbers

Given number ``A``, we need to find if $A=\Sigma$ a<sub>i</sub> where a<sub>i</sub> are consecutive unsigned integer numbers.

* Example 1: ``3 = 1+2``
* Example 2: ``15 = 7+8 = 4+5+6=1+2+3+4+5``
* Example 3: ``22 = 4+5+6+7``
* Example 4: ``8`` is not the sum of any consecutive numbers
## Algorithm

From  a<sub>i</sub> to  a<sub>i+n</sub>, there are totally a<sub>i+n</sub>-a<sub>i</sub>+1 numbers, so there will be (a<sub>i+n</sub>-a<sub>i</sub>+1)/2 total numbers of pairs. 

As $\Sigma$ a<sub>i</sub> = ``sum of each numbers pair  * total number of pairs``

sum of each numbers pair = a<sub>i</sub> + a<sub>i+n</sub>

So $\Sigma$ a<sub>i</sub> = (a<sub>i</sub> + a<sub>i+n</sub>) * (a<sub>i+n</sub>-a<sub>i</sub>+1)/2

While a<sub>i+n</sub> = a<sub>i</sub> + n

So $\Sigma$ a<sub>i</sub> = (2a<sub>i</sub> + n) * (n+1)/2

Shorten a<sub>i</sub> as $a$, $\Sigma$ a<sub>i</sub> will be

$\Sigma$ a<sub>i</sub> = ${ (2a + n)(n+1) } \over 2$

As given $\Sigma$ a<sub>i</sub> = A

So 

A = ${ (2a + n)(n+1) } \over 2$

So that

$a={A\over {n+1} } - {n\over 2 }$

As $a > 0$, so

${A\over {n+1} } - {n\over 2 } \gt 0$ ⇔ ${{2A - n^2 -n}\over {2(n+1)} } \gt 0$

As $n+1 > 0$, so $-n^2 -n + 2A > 0$

We need to find $n$ so that $f(n) = -n^2 -n + 2A \gt 0$. We use the discriminant.

$Δ=1-4(-1)(2A)=1+8A > 0$

As $Δ>0$, for $f(n) > 0$, root $n$ need to be inside the range between $[n1, n2]$ as n1 and n2 are the roots of $f(n)$ equation.

As n>0, so take the postive root of $f(n)$ as $1-\sqrt{1+8A} \over -2$. This will then be treated as the stop condition for $n$ inside the loop checking.

Finally, the unsigned integer number $a$ need to be found needs to sastified:

$$
\left\{
    \begin{array}{ll}
        \ a={A\over {n+1} } - {n\over 2 }\\
        \ {0 < n < {1-\sqrt{1+8A} \over -2}}
    \end{array}
\right.
$$

## Program

[find_the_sum_of_consecutive_numbers.c](find_the_sum_of_consecutive_numbers.c)

Compile: ``gcc find_the_sum_of_consecutive_numbers.c -lm``

# Find the nth digit of an infinite integer sequence

In the infinite integer sequence 123456789101112131415...

* 7th is 7
* For integer number 10: 10th is 1, 11th is 0
* For integer number 11: 12th is 1, 13th is 1

# Analyse the examples

From 1 to 9, there are 1 digit

From 10 to 99 (90 numbers with 2 digits in each number), there are 2*90 = 180 digits

From 100 to 999 (900 numbers with 3 digits in each number), there are 3*900 = 2700 digits

And so on

## 10th

10 = 9 + 1

This indicates that at 10th, it has reached the first 9 numbers (1 to 9), then move to the next number (``+1``)

So 10th will be the first digit of integer number ``10``, which is ``1``

## 11st

11 = 9 + 2 = 9 + 2*1

With 2*1 as 2 digit * 1 number.

This indicates that at 11st, it has finished reaching the first integer number (with 2 digits), after integer number ``9``, which means this integer number is ``10``.

As finish reaching integer number ``10``, 11th will lie in the 2nd digit of ``10``, which is ``0``.

## 12nd

12 = 9 + 2*1 + 1

``2*1`` indicates 12th has reached the first integer number (with 2 digits) after integer number ``9``, then move to the next number as its first digit (``+1``).

* First integer number (with 2 digits) after integer number ``9`` is ``10``
* Move to the next number (integer number ``11``) as its first digit: ``1``

## 13rd

13 = 9 + 2*2

14th has reached 2 integer number after integer number ``9`` as integer number ``11``. So 13th will lie in the 2nd digit of ``11``, which is ``1``.

## 1000th

1000 = 9 + 180 + 3.270 + 1

This indicates that at 1000th, it has reached the 270th integer number after 99 (integer number 99 + 270 = 369) then move to the next number (``370``), as its first digit (``+1``).

So 1000th will lie in the 1st digit of ``370``, which is ``3``.

# Algorithm

Based on the 1000th example:

1000 = 9 * 1 digit + 180 (as 2 digits) + (3 digits) * 270 + 1 (as the residue of 3)

So the program to find the nth digit of an infinite integer sequence will need variables:

* ``number_range``: Count the number range. 1 - 9 has ``number_range=1``, 10 - 99 has ``number_range-2``, 100 - 999 has ``number_range=3``,...
* ``digit_number``: Monitor the change of digit numbers in **the calculation loop**
* ``left_over``: Be the left over. In the ``1000th`` example, ``1`` is the left over.

**The calculation loop** will perform calculation to seperate the number range, digit numbers and the left over. For example with the ``1000th`` example, the calculation loop will result in ``1000 = 9 + 180 + 3.270 + 1``

# Program

```c
#include <stdio.h>

int find_Nth_digit(int n) {
    unsigned int digit_number, number_range, left_over;
    digit_number = number_range = 1;
    while (n > 9 * digit_number * number_range) {
        n -= 9 * digit_number * number_range;
        number_range *= 10;
        digit_number++;
    }
    left_over = number_range + (n - 1) / digit_number;
    for (number_range = (n - 1) % digit_number; number_range < digit_number - 1; number_range++) {
        left_over = left_over / 10;
    }
    return left_over % 10;
}

int main(void)
{
  int n = 1000;
  printf("\n%d digit of the sequence is %d", n, find_Nth_digit(n));//3
  n = 1001;
  printf("\n%d digit of the sequence is %d", n, find_Nth_digit(n));//7
  return 0;    
}
```