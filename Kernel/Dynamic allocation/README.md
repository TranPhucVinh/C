# API

``kzalloc()``: allocate memory like ``kmalloc()`` with the allocated memory set to zero.

```c
char * kstrdup (const char * s,	gfp_t gfp);
```

Allocate space for and copy an existing string

E.g:

```c
int init_module(void)
{
	char *str;
    str = kstrdup("Hello, World !", GFP_KERNEL);
	printk("%s\n", str);

	return 0;
}
```

```c
struct kmem_cache * kmem_cache_create(const char * name, size_t size, size_t align, unsigned long flags, void (*ctor) (void *));
```

Create a cache.

* ``name``: A string which is used in ``/proc/slabinfo`` to identify this cache
* ``size``: The size of objects to be created in this cache
* ``align``: The required alignment for the objects
* ``flags``: SLAB flags
* ``ctor``: A constructor for the objects

```C
void kmem_cache_free(kmem_cache_t *cp, void *obj);
```

Free memory for slab cache ``cp`` and the dynamic allocated object ``obj``

```c
void kmem_cache_destroy(kmem_cache_t *cp);
```

Destroy slab cache object ``cp``

```c
void *kmem_cache_alloc(struct kmem_cache *s, gfp_t flags);
```

# Examples

* [kmalloc() example](kmalloc_example.c), ``kzalloc()`` will work identically.

[kmem_cache example](kmem_cache.c): Dynamic allocation for string char, int and int array

### Notes

If the slab cache declared by ``struct kmem_cache *kmem_cache`` is reused/overwritten by other ``kmem_cache_create()`` without calling ``kmem_cache_destroy()`` like in this case, there will be error.

```c
char *str;
int *number;

kmem_cache = kmem_cache_create("kmem 1", 15, ALIGN_VALUE, SLAB_POISON, CONSTRUCTOR);
str = (char *)kmem_cache_alloc(kmem_cache, GFP_KERNEL);

strcpy(str, "Learn malloc");

printk(KERN_INFO "%s\n", str);
kmem_cache_free(kmem_cache, str);
printk(KERN_INFO "DEBUG: str after kmem_cache_free(): %s\n", str);

kmem_cache = kmem_cache_create("kmem 2", 1, ALIGN_VALUE, SLAB_POISON, CONSTRUCTOR);
number = (int *) kmem_cache_alloc(kmem_cache, GFP_KERNEL);
printk(KERN_INFO "%d\n", *number);
kmem_cache_free(kmem_cache, str);
printk(KERN_INFO "DEBUG: number after kfree(): %d\n", *number);
```

The error will be:

```
Wrong slab cache. kmem 2 but object us from kmem 1
```
