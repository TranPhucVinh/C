### Pointer of pointer

```c
int number1 = 9;

int *ptr = &number1;
int **pptr = &ptr;

int main(){
  printf("ptr: %p \n", ptr);
  printf("pptr: %p \n", pptr);
  printf("**pptr: %d \n", **pptr); //9
}
```