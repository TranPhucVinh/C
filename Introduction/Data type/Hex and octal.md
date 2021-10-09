## Hex

Convert int to hex using ``%x``

```c
int a = 19;
printf("a: 0x%x \n", a); //0x13 
```

Create a hex number from 2 hex variable

```c
char moisure[] = {0x0, 0x74};//Form number 0x0074

char temp_moisure[8];
sprintf(temp_moisure, "0x%x%x", moisure[0], moisure[1]);
```

Convert hex to int

```c
int a = 0x13;
printf("a: %d", a); //19
```

```c
int a = 0xABCD;
printf("a: %d", a); //43981
```

Convert int to hex using ``%p``

```c
int a = 11;
printf("%p", a); //0xb
```

Get first byte and last byte of a 2 byte int variable

```c
int value = 0x1234;
uint8_t lastByte = (uint8_t)value;  //0x34
uint8_t firstByte = value>>8;       //0x12
```
## BCD

BCD encoded for number ``16``: 

```
1 = 0b0001
6 = 0b0110
```

``16`` will be BCD encodded as ``0b00010110``, which will be ``22`` when encoded back to decimal.

```c
// Convert from decimal to BCD
int decToBCD(__uint8_t num)
{
	return ((num/10 * 16) + (num % 10));
}

// Convert from BCD (Binary-Coded Decimal) to Decimal
int bcdToDec(__uint8_t num)
{
	return ((num/16 * 10) + (num % 16));
}
```

## Octal

Octal number is indicated by ``0``

```c
int a = 0777;

printf("%o\n", a);//777
printf("%d\n", a);//511
```
