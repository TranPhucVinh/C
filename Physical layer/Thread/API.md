### Define

Definition in ``pthread.h`` (Windows)

```c
typedef uintptr_t pthread_t;
typedef struct pthread_attr_t pthread_attr_t;
struct pthread_attr_t
{
    unsigned p_state;
    void *stack;
    size_t s_size;
    struct sched_param param;
};
```

Definition in ``_mingw.h`` (Windows)

```c
#define __int64 long long
```

Definition in ``corecrt.h`` (Windows)

```c
#ifndef _PTRDIFF_T_DEFINED
#define _PTRDIFF_T_DEFINED
#ifndef _PTRDIFF_T_
#define _PTRDIFF_T_
#undef ptrdiff_t
#ifdef _WIN64
__MINGW_EXTENSION typedef __int64 ptrdiff_t;
#else
```

### pthread_create()

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

The ``pthread_create()`` function starts a new thread in the calling process. The new thread starts execution by invoking ``start_routine()``; ``arg`` is passed as the sole argument of ``start_routine()``.

The ``attr`` argument points to a ``pthread_attr_t`` structure whose contents are used at thread creation time to determine attributes for the new thread; this structure is initialized using ``pthread_attr_init()`` and related functions. If ``attr`` is ``NULL``, then the thread is created with default attributes.

Before returning, a successful call to ``pthread_create()`` stores the ID of the new thread in the buffer pointed to by ``thread``; this identifier is used to refer to the thread in subsequent calls to other pthreads functions.

On success, ``pthread_create()`` returns ``0``; on error, it returns an ``error number``, and the contents of ``*thread`` are ``undefined``.

### pthread_join()

```c
int pthread_join(pthread_t thread, void **retval);
```

The ``pthread_join()`` function waits for the thread specified by ``thread`` to terminate.  If that thread has already terminated, then ``pthread_join()`` returns immediately. The thread specified by ``thread`` must be joinable.

If ``retval`` is not ``NULL``, then ``pthread_join()`` copies the exit status  of the target thread (i.e., the value that the target thread supplied to ``pthread_exit()``) into the location pointed to by ``retval``.  If the target thread was canceled, then ``PTHREAD_CANCELED`` is placed in the location pointed to by ``retval``.

On success, ``pthread_join()`` returns ``0``; on error, it returns an error number.
