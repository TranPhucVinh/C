### Function pointer

```c
#include <stdio.h>

int add(int a, int b){
	return a+b;
}

int subtract(int a, int b){
	return a-b;
}

double addNumber(int a, double b){
	return a+b;
}

main()
{  
    int (*p)(int, int);
    p = add;
    printf("%d \n",p(5,6)); //11
    p = subtract;
    printf("%d \n",p(5,8)); //-3
    double (*pointer)(int, double);
    pointer = addNumber;
    printf("%f \n", pointer(8, 9.89)); //17.890000 
}
```

### Function pointer as argument

```c
#include <stdio.h>

void abs(){
	printf("Hello world");
}

void helloWorld (void (*function)()){
	function();
}
main()
{ 	
    void (*p)() = abs;
    helloWorld(p);
}
```

**Result:** ``Hello world``

This can be replaced as ``helloWorld(abs);``