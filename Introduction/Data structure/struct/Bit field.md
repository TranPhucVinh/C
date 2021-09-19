Bit field defines the maximum bit that a variable can store in a struct. This will save the memory of a struct.

### Examples

```c
struct time_struct {
    unsigned int hour:5; 	//24: 0b11000
    unsigned int minute:6;	//60: 0b111100
	unsigned int second:6;	//60: 0b111100
};

int main()
{  
    struct time_struct time_value = {24, 60, 60};
	printf("hour:minute:second: %d:%d:%d\n", time_value.hour, time_value.minute, time_value.second);//hour:minute:second: 24:60:60
}
```

If define with ``int``:

```c
struct time_struct {
    int hour:5; 	//24: 0b11000
    int minute:6;	//60: 0b111100
	int second:6;	//60: 0b111100
};

struct time_struct time_value = {24, 59, 59};
printf("hour:minute:second: %d:%d:%d\n", time_value.hour, time_value.minute, time_value.second);//hour:minute:second: -8:-5:-5
```

As ``24`` has its first bit is ``1`` so it will be recognised as a negative number. 2's complement of ``24`` is ``01000`` (as ``-8``).

The same issue happens to ``60``

That issue doesn't happen to the number with the nth bit of ``int number:n`` is ``0``.

```c
struct time_struct {
    int hour:5; 	//24: 0b11000
    int minute:6;	//60: 0b111100
	int second:6;	//60: 0b111100
};

struct time_struct time_value = {11, 31, 31};
printf("hour:minute:second: %d:%d:%d\n", time_value.hour, time_value.minute, time_value.second);//hour:minute:second: 11:31:31
```