A circular linked list is a linked list which connected each other to form a circle

```
Node 1 -> Node 2 -> Node 3 -> ... -> Node 1
```

In this diagram, we can see that the "end" node ``Node n`` which point to Node 1 as its next node, which will form the circle

Based on that definition, for traversing, we need to know the total nodes of the circle linked list.

# Implementation

# Create and read all member of a linked list
[create_and_read_linked_list.c](create_and_read_linked_list.c)

# Verify if a given linked list is a circular linked list

Use two-pointer method, which is a little similar to [Get the middle member of the linked list by 1 time traversing in Singly linked list]() as using 2 pointer ``p1`` and ``p2``.

In every execution of the loop, ``p1`` will access to the next 2 nodes, while ``p2`` only access to its next node. If the linked list is circular, after a number of times, ``p1`` and ``p2`` will point to the same node.

This two-pointer method will also be able to verify this type of circular linked list

![](https://github.com/TranPhucVinh/C/blob/master/Environment/Images/circular_linked_list.jpg)

Program: [verify_linked_list.c](verify_linked_list.c)

# Find the index where the circular linked list start

**Algorithm**: After successfully detecting the linked list is circular, finding the index where the circular linked list starts by:

* Reset the **slow** pointer to the head of the list.
* From this point, move both pointers **slow** and **fast** one step at a time until they meet again. The node where they meet is the start of the cycle.

Program: [find_index_where_circular_linked_list_starts.c](find_index_where_circular_linked_list_starts.c)
