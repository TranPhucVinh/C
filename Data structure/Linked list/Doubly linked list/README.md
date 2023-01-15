### Structure of a Doubly Linked list data structure

```
                 ->        ->
NULL  <- Node 1  <- Node 2 <- Node 3 -> NULL
```

### Create

Create and read all the value from doubly link list, read previous data node from current node: [create_and_read_linked_list.c](create_and_read_linked_list.c)

Insert a new node to existed link list with index: [insert_at_index.c](insert_at_index.c)

### Read

* Read all nodes from linked list: Check ``create.c`` from ``Create``
* Read node value at specific index: ``read_with_index.c``
    * Argument 1: Index of the node to read to check the linked list integrity

### Update

Update node value at specific index (the only way to find a node at a specific index is to looping the whole link list): ``update_index.c``

Argument when executing:
* Argument 1: Index to update value
* Argument 2: ID value of the updated node
* Argument 3: Integer value of the updated node
* Argument 4: Index of the node to read to check the linked list integrity

### Delete

Delete node at specific index: ``delete_node_with_index.c``

Argument when executing:

* Argument 1: Index to delete
* Argument 2: Index of the node to read to check the linked list integrity