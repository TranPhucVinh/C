``int``: overflow value is 2147483647 (4-b

### stdint.h

Library **stdint** include integer types.

```c
int8_t
int16_t
int32_t
uint8_t
uint16_t
uint32_t
```

### Data Type 

**uint8_t**: 8 bit unsigned int.

**E.g**: Example with **bit overflow**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     
#include <stdint.h>

uint8_t return8BitNumber(uint8_t number){
    return number;
}

int main (){
  printf("8 bit number is: %d", return8BitNumber(1023)); //1023: 10 bit
}
```

**Compile**:  

```
warning: large integer implicitly truncated to unsigned type [-Woverflow]
printf("8 bit number is: %d", return8BitNumber(1023));
```

**Result**

```
8 bit number is: 255
```

**With signed number**

```c
printf("8 bit number is: %d", return8BitNumber(-9));
```

```
8 bit number is: 247
```

```
247 = 11110111 
9 = 1001 => -9 = 9 (implement 1) + 1 = 0110 + 1 = 1111 0111
```

### Convert to char

**1st way**

```c
uint8_t return8BitNumber(uint8_t number){
    return number;
}

int main (){
  printf("Char with correspond ASCII code: %c", return8BitNumber(80));
}
```

**2nd way**

```c
uint32_t return8BitNumber(uint32_t number){
    return number;
}

int main (){
  char returnChar;
  returnChar = (char) return8BitNumber(80);
  printf("8 bit number is: %c", returnChar);
}
```

```
Char with correspond ASCII code: P
```

### Convert unsigned int to String

```c
uint32_t return8BitNumber(uint32_t number){
    return number;
}

int main (){
  char returnChar[1];
  // int returnInt = return8BitNumber(80);
  sprintf(returnChar, "%d",  return8BitNumber(80));
  printf("String is: %s", returnChar);
}
```

```
String is: 80    
```

### size_t

**size_t** is actually **long unsigned int**.

```c
typedef unsigned int size_t;
```

So if the value of variable with **size_t** is negative, the result will be unpredictable

```c
size_t a = 0;
cout << a-2 << endl; //18446744073709551614
return 0;
```
