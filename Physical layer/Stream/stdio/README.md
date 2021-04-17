* ``readAndStore.c``: Read 10 bytes data from every line of file ``json.txt`` then store in an array string

``json.txt``

```
170604d9cc
180604d9cc
1e0604d9cd
```

**Notice**: For 10 byte data and a new line (``\n``) to read in ``fgets()``, the read buffer must be 12 bytes (for ``n-1`` byte read).