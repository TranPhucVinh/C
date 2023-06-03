# API

## kzalloc()

``kzalloc()`` allocates memory like ``kmalloc()`` with the allocated memory set to zero.

```c
void * kzalloc(size_t size, gfp_t flags);
```
**Get size**: Just like [malloc()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/Using%20stdlib.md#malloc),  there is no portable way to find out the size of a kmalloc'ed block.

## kstrdup()

```c
char *kstrdup(const char *, gfp_t gfp);
```

Allocate space for and copy an existing string

E.g:

```c
int init_module(void)
{
	char *str;
    str = kstrdup("Hello, World !", GFP_KERNEL);
	printk("%s\n", str);//Hello, World !

	return 0;
}
```
## krealloc()
```c
void * krealloc(const void * p, size_t new_size, gfp_t flags);
```
Reallocate memory, correspond to [realloc()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/API.md#realloc) in userspace
```c
char *str;

/* Initial memory allocation */
str = (char *) kmalloc(15, GFP_KERNEL);
strcpy(str, "Learn malloc");
printk(KERN_INFO "%s\n", str);// Learn malloc
str = krealloc(str, 20, GFP_KERNEL);
strcpy(str, "Hello, World !");
printk(KERN_INFO "%s\n", str);// Hello, World !
kfree(str);
```

## kfree()
```c
void kfree(const void * objp);
```
## kmem_cache_create()
```c
struct kmem_cache *kmem_cache_create(const char * name, size_t size, size_t align, unsigned long flags, void (*ctor) (void *));
```

Create a cache.

* ``name``: A string which is used in ``/proc/slabinfo`` to identify this cache
* ``size``: The size of objects to be created in this cache
* ``align``: The required alignment for the objects
* ``flags``: SLAB flags
* ``ctor``: A constructor for the objects

## kmem_cache_alloc()

```c
void *kmem_cache_alloc(struct kmem_cache *s, gfp_t flags);
```

## kmem_cache_free()

```c
void kmem_cache_free(kmem_cache_t *cp, void *obj);
```

Free memory for slab cache ``cp`` and the dynamic allocated object ``obj``

## kmem_cache_destroy()

```c
void kmem_cache_destroy(kmem_cache_t *cp);
```

Destroy slab cache object ``cp``
# Examples

## [kmalloc() example](kmalloc_example.c)

* Implement ``kmalloc()`` for ``int``, ``int array`` and string as ``char pointer``.
* ``kzalloc()`` will work identically.

## [kmem_cache example](kmem_cache.c)

Dynamic allocation for string char, int and int array

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
