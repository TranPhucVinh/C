### Add number with struct issue

```c
#include <stdio.h>
struct complex
{
	int real;
	int imaginary;
} complex1, complex2, complexNumber;

void resultNumber(struct complex complex1, struct complex complex2, struct complex complexNumber);

main(){
	complex1.real = 1;
	complex1.imaginary = 2;
	complex2.real = 3;
	complex2.imaginary = 4;

    resultNumber(complex1, complex2, complexNumber);
    printf("Complex number: %d +i%d", complexNumber.real, complexNumber.imaginary);
}

void resultNumber(struct complex complex1, struct complex complex2, struct complex complexNumber){
	complexNumber.real = complex1.real + complex2.real;
	complexNumber.imaginary = complex1.imaginary + complex2.imaginary;
}
```

**Result** ``Complex number: 0 +i0``

=> This is the problem with pointer

### Solve

```c
#include <stdio.h>
struct complex
{
	int real;
	int imaginary;
} complex1, complex2, complexNumber;

void resultNumber(struct complex complex1, struct complex complex2, struct complex *complexNumber);

main(){
	complex1.real = 1;
	complex1.imaginary = 2;
	complex2.real = 3;
	complex2.imaginary = 4;

    resultNumber(complex1, complex2, &complexNumber);
    printf("Complex number: %d +i%d", complexNumber.real, complexNumber.imaginary);
}

void resultNumber(struct complex complex1, struct complex complex2, struct complex *complexNumber){
	complexNumber->real = complex1.real + complex2.real;
	complexNumber->imaginary = complex1.imaginary + complex2.imaginary;
}
```
**Result** ``Complex number: 4 +i6``

### Syntax

* ``(.)`` is used to access the instance inside a **struct**.
* ``(->)`` is used by **pointer struct** to access the inside instance.
