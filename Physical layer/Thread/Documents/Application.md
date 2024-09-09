# Use multiple threads for calculation

[Use 2 threads to calculate the sum from 1 to 2147483646](src/sum_from_1_to_n.c). This example will take 3 seconds to perform while [the raw function call](https://github.com/TranPhucVinh/C/blob/master/Algorithms/sum_from_1_to_n.c) will take 5 seconds to execute.

Using 3 threads will cause overflow error when compiling:

```c
range_1.lower_range = 0;
range_1.upper_range = N/3;

range_2.lower_range = N/3 + 1;
range_2.upper_range = 2*N/3;

range_3.lower_range = 2*N/3 + 1;
range_3.upper_range = N;
```

Problem solve: 

```c
range_1.lower_range = 0;
range_1.upper_range = N/3;

range_2.lower_range = N/3 + 1;
range_2.upper_range = N/3 + N/3;

range_3.lower_range = N/3 + N/3 + 1;
range_3.upper_range = N;
```
# [Multithread HTTP server built on TCP API](https://github.com/TranPhucVinh/C/tree/master/Application%20layer/HTTP%20server#multithread-http-server-built-on-tcp-api)
