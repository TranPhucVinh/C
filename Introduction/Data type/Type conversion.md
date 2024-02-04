# Fundamental concepts

There are two types of type conversion:
* [Implicit Type Conversion](#implicit-type-conversion), also known as automatic type conversion.
* [Explicit Type Conversion](#explicit-type-conversion): This process is also called **type casting** and it is user-defined. The user can typecast the result to make it of a particular data type, i.e **changing an expression from one data type to another**. 

# Implicit type conversion

* **Implicit Type Conversion** is **done by the compiler** on its own, without any external trigger from the user.
* Generally takes place when in an expression more than one data type is present. In such condition, type conversion (also called **type promotion**) takes place to avoid lose of data.
* It is possible for implicit conversions to lose information, signs can be lost (when signed is implicitly converted to unsigned), and overflow can occur (when long long is implicitly converted to float).

For integer number, the implicit type conversion path will be:

```
bool -> char -> short int -> int
```

```c
int x = 10; // integer x
char y = 'a'; // character c

// y implicitly converted to int. ASCII
// value of 'a' is 97
x = x + y;

// x is implicitly converted to float
float z = x + 1.0;

printf("x = %d\n", x);//107
printf("y = %c\n", y);//a
printf("z = %f\n", z);//108.0000
```

## Implicit casting for float to int

```c
int b = 3.1;
printf("%d \n", b); //3
printf("%f \n", b); //0.0
```
Implicit casting in ``printf()`` for float to int:
```c
float c = 3.1;
printf("%d \n", c); //-1073741824
```

## Implicit casting during calculation

```c
int a = (998/1024)*100; // a = 0
```

# Explicit type conversion

Explicit Type Conversion, which is user-defined, allows user to **typecast the result** to make it of a particular data type.

**Syntax**

```
(type) expression
```

## double to int

```c
double x = 1.2;

// Explicit conversion from double to int
int sum = (int)x + 1;

printf("sum = %d\n", sum);//2
```

## float to Int

```c
int a = (int) 12.9;
printf("%d \n", a);	//12
printf("%f \n", a); //0
```

## int to float

```c
float a = (float) 3;
printf("%d \n", a);	//0
printf("%f \n", a); //3.000
```    
