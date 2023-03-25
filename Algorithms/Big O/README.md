Big O notation (with a capital letter ``O``, not a zero; normally written as ``O()``), also called Landau's symbol, is a symbolism used in complexity theory, computer science, and mathematics to describe the asymptotic behavior of functions. Basically, it tells you how fast a function grows or declines.

For the formal definition, suppose ``f(x)`` and ``g(x)`` are two functions defined on some subset of the real numbers. We write

``f(x) = O(g(x))``, for ``x -> ∞``

If and only if there exist constants ``N`` and ``C`` such that:

|f(x)| ≤ C |g(x)| for all ``x >N``

Intuitively, this means that ``f(x)`` does not grow faster than ``g(x)``

# Find O(n), C and N of a given function

f(x) = ${3n^2 + 5}$

With C=4 N=2, f(x) is ${O(n^2)} as with all n > 2

${3n^2 + 5 \le 4n^2}$