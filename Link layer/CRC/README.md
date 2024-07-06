# Fundamental concepts

## CRC calculation

A Transmitted data is represented by a polynomial (E.g 0011 is represented by ``X(x)=x+1``)

Polynomial representations: ``H(x)=x^r + x^r-1 + x^r-2 + ... + x + 1``. Polynomial representations is specifically defined base on specific applications 

E.g Polynomial representations for CRC-16-IBM is ``x^16+x^15+x^2+1``

CRC is defined as a redundancy from the division of ``x^r*X(x)/H(x)``. Notice the divison calculate ``0-1=1``.

So the totally transmitted data will be: ``T(x) = x^r*X(x) + CRC``

The receiver will perform ``T(x)/H(x)``. If the redudancy is ``0``, then there will be zero error in transmission.

### Example

Transmitted data is ``0011`` (``X(x)=x+1``)

Polynomial representations is ``H(x)=x^3+x+1``

``x^3*X(x) = x^4+x^3`` (Left shit 3 bit)

Redundancy of ``x^3*X(x)/H(x)`` is ``x^2 + 1``

The transmitted data will then be: ``T(x) = x^3*X(x) + CRC = x^4 + x^3 + x^2 + 1``

# CRC implementations

Check [CRC implementations document](CRC%20implementations.md) for specific CRC implementations.
