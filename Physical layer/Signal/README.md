All signals are defined in library ``signal.h`` in C Standard Library.

## API

### signal()

``signal()``: sets a function to handle signal

```c
sighandler_t signal(int signum, sighandler_t signal_handler);
```

* ``signum``: The signal number to which a handling function is set.
* ``signal_handler``: The ``signal_handler`` function has prototype

```c
void signal_handler(int signalNumber);
```

### sigset_t

* ``sigset_t``: represents a set of signals
* ``int sigemptyset (sigset_t *set)``: This function initializes the signal set set to exclude all of the defined signals. It always returns 0.
* ``int sigfillset (sigset_t *set)``: This function initializes the signal set set to include all of the defined signals. The return value is 0.
* ``int sigaddset (sigset_t *set, int signum)``: This function adds the signal ``signum`` to the signal set ``set``. All ``sigaddset()`` does is modify ``set``; it does not block or unblock any signals.
* ``int sigdelset (sigset_t *set, int signum)``: This function removes the signal ``signum`` from the signal set ``set``. All ``sigdelset`` does is modify ``set``; it does not block or unblock any signals. The return value and error conditions are the same as for sigaddset.
* ``int sigismember (const sigset_t *set, int signum)``: The ``sigismember`` function tests whether the signal signum is a member of the signal set ``set``. It returns ``1`` if the signal is in the ``set``, ``0`` if not, and ``-1`` if there is an error.

``int sigprocmask (int how, const sigset_t *restrict set, sigset_t *restrict oldset)``: The ``sigprocmask`` function is used to examine or change the calling process’s signal mask.

The last argument, ``oldset``, is used to return information about the old process signal. mask.

Values for the ``HOW`` argument to `sigprocmask'

```c
#define	SIG_BLOCK     0		 /* Block signals.  */
#define	SIG_UNBLOCK   1		 /* Unblock signals.  */
#define	SIG_SETMASK   2		 /* Set the set of blocked signals.  */
```