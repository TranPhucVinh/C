# API

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

[Example with kmalloc()](kmalloc_example.c)