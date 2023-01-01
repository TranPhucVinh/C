# Find if a given number is the sum of consecutive numbers

Given number ``A``, we need to find if $A=\Sigma$ a<sub>i</sub> where a<sub>i</sub> are consecutive unsigned integer numbers.

* Example 1: ``3 = 1+2``
* Example 2: ``15 = 7+8``
* Example 3: ``22 = 4+5+6+7``

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
