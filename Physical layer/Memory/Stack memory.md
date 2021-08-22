Stack memory is a temporary memory allocation scheme where the data members are accessible only if the method( ) that contained them is currently is running.

```c
int main()
{
   // All these variables get memory
   // allocated on stack
   int a;
   int b[10];
   int n = 20;
   int c[n];
}
```