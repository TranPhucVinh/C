# Classification

Graph can be classified to directed and undirected graph.

# Visualize a graph

``graphviz`` can be used to draw a graph.

Install: ``sudo apt install graphviz``

Command ``dot``:

* ``-Tpdf``: Output the graph to pdf

File ``.dot``, e.g ``test.dot``, is used to store graph information.

Undirected graph:
```
graph {
    a -- b;
    b -- c;
}
```

``graph`` and ``--``: undirected graph

Directed graph:
```
digraph {
    a -> b;
    b -> c;
}
```

``dgraph`` and ``->``: directed graph

``dot test.dot -Tpdf > graph.pdf``: Draw the graph from ``test.dot``, output to ``graph.pdf``.

# Represent a graph

A graph can be represented by a square matrix (2D array), which is called adjacency matrix. If node ``i`` is connected to node ``j``, A[i,j] = 1

For directed graph, there can be a case like node ``i`` connects to node ``j``, which results in ``A[i,j] = 1``, while node ``j`` doesn't connect to node ``i``, which results in ``A[j,i] = 0``.

Build an adjacency matrix to present a directed graph:

* ``init_graph()``
* ``add_edge()``
* ``delete_edge()``
* ``print_graph()``

Program: [adjacency_matrix_graph.c](adjacency_matrix_graph.c)
# DFS

**Question**: What is the meaning/application of the DFS output in graph, binary tree as this output doesn't seem to give any information to state which path is traversed to get this output ? When investigating the DFS output, which information does it provide us ?

**Answer**: Searching data in a raw database (i.e database stored without any arrangement/ordered by a specific key) is inefficient. For efficient searching, database arrangement from the raw one is required.
A suggestion for that can be:

Raw database -> Specific key increment/decrement database (achieved by sorting algorithm) -> traversal table outputted by binary search.

We finally use that traversal table for searching, which will result in efficient search compared to raw database searching.
