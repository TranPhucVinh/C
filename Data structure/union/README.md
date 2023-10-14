A union is a special data type available in C that allows to store different data types in the same memory location.

# Define

```c
union data {
   int i;
   float f;
   char str[20];
} data; 
```

As the whole union is stored in the same memory location, this will give logical error:

```cpp
data.i = 1;
data.f = 1.0;
strcpy(data.str, "hello");

printf("i: %d \n", data.i); //i: 1819043176 
printf("f: %f \n", data.f); //f: 1143141483620823940762435584.000000 
printf("str: %s \n", data.str);//str: hello 
```

**Exlain**: Variable f corrupt because the final value assigned to the variable has occupied the memory location and this is the reason that the value of str member is getting printed very well.

When setting the value with smaller data type like below, that smaller data type won't be affected:

```c
#include <stdio.h>

union data {
   int int_value;
   char char_value;
} data; 

int main (){
   data.int_value = 19;
   printf("%d", data.int_value);//19
   printf("%d", data.char_value);//19
}
```

## Problem solved

```c
data.i = 1;
printf( "data.i : %d\n", data.i);

data.f = 1.0;
printf( "data.f : %f\n", data.f);

strcpy( data.str, "hello");
printf( "data.str : %s\n", data.str);
```

Or set the value to buffer

```c
char int_buffer[10];
char float_buffer[10];
char string_buffer[10];

data.i = 1;
sprintf(int_buffer, "i: %d\n", data.i);

data.f = 1.0;
sprintf(float_buffer, "f: %lf\n", data.f);

strcpy(data.str, "hello");
sprintf(string_buffer, "str: %s\n", data.str);

printf("%s", int_buffer); //i: 1
printf("%s", float_buffer); //f: 1.000000
printf("%s", string_buffer);//str: hello 
```

# Size

``union`` has the size of its biggest data type member

```c
union Data {
   int i;
   float f;
   char str[20];
} data; 

printf("size of data: %d", sizeof(data)); //20: size of str[20]
```

# union as function argument

```c
#include <stdio.h>
#include <string.h>

union data {
   int i;
   float f;
   char str[20];
}; 

void unionFunction(union data data0);

int main(){
    union data dataObject;
    unionFunction(dataObject);
}

void unionFunction(union data data0){
    data0.i = 1;
    printf("data.i: %d\n", data0.i);

    data0.f = 1.0;
    printf("data.f: %f\n", data0.f);

    strcpy( data0.str, "hello");
    printf("data.str: %s\n", data0.str);
}
```
# [Union for string parsing]()
* [Union packing 4 8-bit int numbers to a 32-bit number]()
* [Parse a char array into 3 smaller char array]()
* [Parse a char array into smaller chars and numbers]()
