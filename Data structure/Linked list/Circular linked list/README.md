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

Use the same method of [Get the middle member of the linked list by 1 time traversing in Singly linked list]() as using 2 pointer ``p1`` and ``p2``.

In every execution of the loop, ``p1`` will access to the next 2 nodes, while ``p2`` only access to its next node. If the linked list is circular, after a number of times, ``p1`` and ``p2`` will point to the same node.

Program: [verify_linked_list.c](verify_linked_list.c)