# O(1)

```c
int display(int n){
    return 0;
}
```
``display()`` has O(1) because no matter what the input ``n`` is, it only returns ``0`` and takes no further calculation.

# O(n)

```c
void display(int n){
    for (int i = 0; i < n; i++){
        printf("%d\n", i);
    }
}
```

``display()`` has O(n) as this function grows by ``n``.

```c
int display(int n){
    for (int i = 0; i < n; i++){// O(n)
        printf("Hello, world !\n"); // O(1)
        int a = 4;// O(1)
        printf("%d\n", a);// O(1)
    }
    return 0;
}
```

``display()`` function will have the Big-O = O(n) + O(1) + O(1) + O(1) = O(n)

# ${O(n^2)}$

```c
int display(int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d %d\n", i, j);
        }
    }
    return 0;
}
```

# ${O(n^3)}$
```c
int display(int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                printf("%d %d %d\n", i, j, k);
            }
        }
    }
    return 0;
}
```