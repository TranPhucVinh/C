# Structure of a Singly Linked list data structure

```
Node 1 -> Node 2 -> Node 3 -> ... -> NULL
```

For memory storage reason, linked list must be implemented on heap memory.

# [Implementations](Implementations.md)

* [Create](Implementations.md#create): Create and read all member of a linked list, insert a new node to an existed linked list by the specified index
* [Read](Implementations.md#read): [Read the whole linked list](), [read a node at specific index](), get linked list size, get the middle member of the linked list by 1 time traversing
* [Update](Implementations.md#update): Update node value at a specific index
* [Delete](Implementations.md#delete): Delete node at specific index (at index 0, middle index and the last index)

# Examples

* Create linked list from a given array: [array_to_linked_list.c](array_to_linked_list.c)
* Create an array from a given linked list: [linked_list_to_array.c](linked_list_to_array.c)
