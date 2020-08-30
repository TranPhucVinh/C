### Structure of a Singly Linked list data structure

```
Node 1  -> Node 2 -> Node 3 -> ... -> NULL
```

### Create

* Create a link list and add new node to existed link list: ``create.c``

* Insert a new node to existed link list with index and value from command line: ``create_with_index.c``

    * ``Argument 1``: Index to insert the new node
    * ``Argument 2``: ID value of the inserted node
    * ``Argument 3``: Integer value of the inserted node

### Read

* Read all nodes from linked list with the first node as argument: ``read_with_first_node.c``
* Read all nodes from linked list without the first node as argument: ``read_without_first_node.c``
* Read node value at specific index (the only way to find a node at a specific index is to looping the whole link list): ``read_with_index.c``
    * ``Argument 1``: Index of the node to read

### Update

Update node value at specific index (the only way to find a node at a specific index is to looping the whole link list): ``update_with_index.c``

Argument when executing: 

* ``Argument 1``: Index to update value
* ``Argument 2``: ID value of the updated node
* ``Argument 3``: Integer value of the updated node

### Delete

Delete node at specific index: ``delete_node_with_index.c``

Argument when executing: 

* ``Argument 1``: Index to delete