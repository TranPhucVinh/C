``int``: overflow value is ``2147483647`` (4-byte)

### stdint.h

Library **stdint** include integer types.

| Type | Signing|Value range|
| ------- |------|------|
|int8_t |Signed|-127 to 127|		
|uint8_t |Unsigned|0 to 255|		
|int16_t |Signed|−32,768 to 32,767|
|uint16_t |Unsigned|0 to 65,535|
|int32_t |Signed|−2,147,483,648 to 2,147,483,647|
|uint32_t (unsigned int)|Unsigned|0 to 4,294,967,295|
|int64_t|Signed| −9,223,372,036,854,775,808	to 9,223,372,036,854,775,807|
|uint64_t|Unsigned|0 to 18,446,744,073,709,551,615|

``%u`` is used for unsigned int.

``int`` uses its first bit for number sign.

### Examples

**Example 1**

For examples with signed number and overflow number, check: ``Data type/Char for integer.md``

**Example 2**

Overflow issue inside for loop with ``uint8_t``:

```c
for (uint8_t i = 0; i < 256; i++){
  printf("i: %d\n", i);
}
```

This for loop will run forever as max value of ``uint8_t`` is ``255``. When ``i`` reaches ``256``, it will be ``0``.

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

### Convert unsigned int to string char array

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
