# Structure of a Singly Linked list data structure

```
Node 1 -> Node 2 -> Node 3 -> ... -> NULL
```

For memory storage reason, linked list must be implemented on heap memory.

# [Create](Create.md)
* Create and read all member of a linked list, insert a new node to an existed linked list by the specified index
* Why a node on stack memory can't be inserted to the linked list ?
* Create linked list from a given array: [array_to_linked_list.c](array_to_linked_list.c)
* Create an array from a given linked list: [linked_list_to_array.c](linked_list_to_array.c)
# [Read](Read.md)
* [Read the whole linked list](), [read a node at specific index]()
* Get linked list size, get the middle member of the linked list by 1 time traversing
# [Update](Update.md)
* [Update node value at a specific index](update_at_specific_index.c)
* Reverse the linked list
# Delete
Delete node at specific index (at index 0, middle index and the last index (function **delete_node_at_index()** in [linked_list_operations.c](linked_list_operations.c)).
