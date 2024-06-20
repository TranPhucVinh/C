# Structure of a Singly Linked list data structure

```
Node 1 -> Node 2 -> Node 3 -> ... -> NULL
```

For memory storage reason, linked list must be implemented on heap memory.

# Implementations

* [Create](Create.md): Create and read all member of a linked list, insert a new node to an existed linked list by the specified index
* [Read](Read.md): [Read the whole linked list](), [read a node at specific index](), get linked list size, get the middle member of the linked list by 1 time traversing
* **Update**: [Update node value at a specific index](update_at_specific_index.c)
* **Delete**: [Delete node at specific index (at index 0, middle index and the last index)](delete_at_specific_index.c)

# Examples

* Create linked list from a given array: [array_to_linked_list.c](array_to_linked_list.c)
* Create an array from a given linked list: [linked_list_to_array.c](linked_list_to_array.c)
