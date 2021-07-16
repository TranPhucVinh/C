### Address of a struct

```c
struct student{
		int id;
		char name[50];
		char classroom[50];
};

int main() {
	struct student erin = { 1977, " Erin", "Free Lancer" };

	printf("value &erin: %p \n", &erin); //0x7ffe09debe80
	printf("value &erin.id: %p \n", &erin.id); //0x7ffe09debe80
	printf("value &erin.name: %p \n", &erin.name); //0x7ffe09debe84
	printf("value &erin.classroom: %p \n", &erin.classroom); //0x7ffe09debeb6
}
```

Address of ``erin`` and ``erin.id`` are the same.

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
