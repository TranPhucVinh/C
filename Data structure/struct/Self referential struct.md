# Self Referential Structure with Single Link

```c
#include <stdio.h> 
  
struct databaseNode { 
    int id;
    int intValue;
    struct databaseNode* link; 
}; 
  
int main() 
{ 
    struct databaseNode node1 = {1, 10};
    struct databaseNode node2 = {30, 40};
    node1.link = &node2;
    
    // Accessing data members of node2 using node1 
    printf("Node 2 ID node1.link->id: %d \n", node1.link->id); 
    printf("Node 2 intValue node1.link->intValue: %d \n", node1.link->intValue); 
    return 0; 
} 
```
**Output**
```
Node 2 ID node1.link->id: 30
Node 2 intValue node1.link->intValue: 40
```
# Self Referential Structure with Multiple Links

Created a link data structure node like this

```
        ->        ->
Node 1  <- Node 2 <- Node 3
```

```c
#include <stdio.h>

struct databaseNode { 
    int id; 
    struct databaseNode* prev_link; 
    struct databaseNode* next_link; 
}; 
  
int main() 
{ 
    struct databaseNode node1 = {1}; //Node 1 
    
    struct databaseNode node2 = {2}; //Node 2

    struct databaseNode node3 = {3}; //Node 3 
  
    // Next links 
    node1.next_link = &node2; 
    node2.next_link = &node3; 
  
    // Previous links 
    node2.prev_link = &node1; 
    node3.prev_link = &node2; 
  
    // Accessing  id of node1, node2 and node3 by node1 
    printf("%d\t", node1.id); 
    printf("%d\t", node1.next_link->id); 
    printf("%d\n", node1.next_link->next_link->id); 
  
    // Accessing id of node1, node2 and node3 by node2 
    printf("%d\t", node2.prev_link->id); 
    printf("%d\t", node2.id); 
    printf("%d\n", node2.next_link->id); 
  
    // Accessing id of node1, node2 and node3 by node3 
    printf("%d\t", node3.prev_link->prev_link->id); 
    printf("%d\t", node3.prev_link->id); 
    printf("%d", node3.id); 
    return 0; 
} 
```
**Output**
```
1       2       3
1       2       3
1       2       3
```

# Applications

Self referential structures are very useful in creation of other complex data structures:

* Linked Lists
* Stacks
* Queues
* Trees
* Graphs