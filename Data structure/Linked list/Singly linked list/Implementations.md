# Create

* Create and read all member of a linked list: [create_and_read_linked_list.c](create_and_read_linked_list.c)
* Insert a node on heap memory into to the linked list on stack memory: [insert_with_index_stack_memory.c](insert_with_index_stack_memory.c)
* Insert a node on heap memory into to the linked list on heap memory: [insert_with_index_heap_memory.c](insert_with_index_heap_memory.c)
  
**Create/insert a node at index 0 (node 1)**:

Old linked list

```
Node 1 (old node) -> Node 2 -> Node 3 -> ... -> NULL
```

New linked list

```
Node 1 (new node) -> Node 1 (inserted node/old node) -> Node 2 -> Node 3 -> ... -> NULL
```

As traversing linked list started from node 1, the inserted node is actually node 1 old node (in the diagram above), while node 1 new node just has its value updated.

So in this diagram:

* Node 1 new node has the address of node 1 old node but has latest inserted value
* Node 1 old node is a newly created node and has the value of node 1 old node

So the inserted node is a temporary node to stored the value of node 1 old node.

Check implementation for this in [insert_with_index_heap_memory.c](insert_with_index_heap_memory.c) program. This program supports inserting a new node to an existed linked list by the specified index. Function ``insert_node_at_index()`` supports inserting a new node at index 0 (beginning of the linked listed) and at the middle index. If the insert node is at index = linked list size, the linked list will appended.

There is another way to insert a node at first index is to use double pointer, check [multiple_defines_for_insert_with_index.c](multiple_defines_for_insert_with_index.c) source code.

**Notes**: ``ins_node``, which is used to insert a new node into the linked list with existed nodes on [stack](insert_with_index_stack_memory.c#L36) or [heap](insert_with_index_heap_memory.c#L41) memory, must always be on heap memory, i.e dynamically allocated by [malloc()](https://github.com/TranPhucVinh/C/blob/master/Physical%20layer/Memory/Dynamic%20memory%20allocation/API.md#malloc), as its address won't be changed outside **insert_node_at_middle()** function.

**Why a node on stack memory can't be inserted to the linked list ?**

Function ``insert_node_at_middle()`` with a node on stack memory, i.e ``static LinkedList ins_node``, can only be called one time as using ``static LinkedList ins_node`` makes its address can't be changed in the next time calling this function:

```c
// THIS IS A WRONG IMPLEMENTATION TO INSERT A NODE. MUST NOT PRACTICE ITS IN REAL APPLICATION
int insert_node_at_middle(LinkedList *first_node, int index, int id, int value){
    int size;
    LinkedList *current_node = first_node;
    LinkedList *prev_node;
    static LinkedList ins_node;

    int tmp_index = 0;

    ins_node.id = id;
    ins_node.value = value;

    // With static LinkedList ins_node, we can't insert a new node to node 1
    while(current_node != NULL)
	{        
      	if (tmp_index == index) {
            prev_node->next_node = &ins_node;
			ins_node.next_node = current_node;
			return 1;
      	}
        prev_node = current_node;  
		current_node = current_node->next_node;
		tmp_index++;
    }

	size = tmp_index;

	if (index == size){
		prev_node->next_node = &ins_node;
		return 1;
	}  
    return 0;
}
int main() 
{ 
    struct database_node node_0 = {1, 100};

    struct database_node node_1, node_2;
    insert_new_node(&node_0, &node_1, 2, 200);
    insert_new_node(&node_1, &node_2, 3, 300);
    insert_new_node(&node_1, &node_2, 4, 400);
    node_2.next_node = NULL; //End link list

	printf("Before updating:\n");
    display_link_list(&node_0);

    insert_node_at_middle(&node_0, 1, 123, 456);

	printf("After updating:\n");
	display_link_list(&node_0);

// Calling insert_node_at_middle(&node_0, 1, 123, 456) one more time insert a new node
// result in infinite inserting due to while(current_node != NULL); as using static LinkedList ins_node
    return 0; 
} 
```

# Read

## Read the whole linked list

Check [create_and_read_linked_list.c](create_and_read_linked_list.c) source code, with function ``display_linked_list()`` to display the whole linked list. Note that ``first_node`` as parameter of ``display_linked_list()`` must be passed by reference as linked list performs traversing based on the address, which started from first node.

## Read a node at specific index

Function ``read_at_index()``

```c
//Other operations like in create_and_read_linked_list.c
int read_at_index(struct database_node *first_node, int index){
    struct database_node *ptr = first_node;
    int tmp_index = 0;
    while(ptr != NULL)
	{
        if (tmp_index == index) {
            printf("index: %d, (%d,%d)", index, ptr->id, ptr->value);
            return 1;
        }    
        tmp_index += 1;
        ptr = ptr->next_node;
    }
	printf("There is no index %d in linked list\n", index);
    return 0;
}

int main() 
{ 
	struct database_node *node_0, *node_1, *node_2;
	node_0 = (struct database_node *)malloc(sizeof(struct database_node));

    node_0->id = 1;
    node_0->value = 100;

    node_1 = (struct database_node *)malloc(sizeof(struct database_node));
    node_2 = (struct database_node *)malloc(sizeof(struct database_node));
    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = NULL; //End link list
	display_linked_list(node_0);

    read_at_index(node_0, 0);

    return 0; 
}
```
Implement ``read_at_index()`` by recursive:

```c
int read_at_index(struct database_node *first_node, int index){
    struct database_node *ptr = first_node;
    static int _index = 0;

    if (first_node == NULL) {
        printf("There is no index %d in linked list\n", index);
        return 0;
    }
    if (_index == index) {
        printf("index: %d, (%d,%d)", index, ptr->id, ptr->value);
        return 1;
    }
    _index += 1;    
    return read_at_index(ptr->next_node, index);
}
```

## Size of a linked list

Size of the linked list can only be gotten by traversing the whole list.

## Get the middle member of the linked list by 1 time traversing

To get the middle member of the linked list, beside the traditional way is to [get the list size](#size-of-a-linked-list) first for later calculate the index of the middle member, the middle member can be access by 1 time traversing. The algorithm is to use 2 pointer, ``p1`` and ``p2``.

In every execution of the loop, ``p1`` will access to the next 2 nodes, while ``p2`` only access to its next node. So when ``p1`` has reached the end of the linked list, ``p2`` has reached to the middle node.

```c
//Other part are like create_and_read_linked_list.c
void get_middle(struct database_node *first_node){
    struct database_node *p1, *p2;
    p1 = first_node;
    p2 = first_node;

    while ((p1->next_node) && (p1->next_node->next_node)){
        p2 = p2->next_node;
        p1 = p1->next_node->next_node;
    }
    printf("Middle node (%d,%d) ", p2->id, p2->value);
}

int main() 
{
    //Other part are like create_and_read_linked_list.c
    get_middle(node_0); 
}
```

# Update

Update node value at a specific index, then display the linked list before and after updating to see changes:

```c
//Other operations like in create_and_read_linked_list.c
int update_node_at_index(struct database_node *first_node, int index, int id, int value){
    struct database_node *ptr = first_node;
    int tmp_index = 0;

    while(ptr != NULL)
	{
        if (tmp_index == index) {
			ptr->id = id;
			ptr->value = value;
            return 1;
        }    
        tmp_index += 1;
        ptr = ptr->next_node;
    }
    return 0;
}

int main() 
{ 
	struct database_node *node_0, *node_1, *node_2;
	node_0 = (struct database_node *)malloc(sizeof(struct database_node));

    node_0->id = 1;
    node_0->value = 100;

    node_1 = (struct database_node *)malloc(sizeof(struct database_node));
    node_2 = (struct database_node *)malloc(sizeof(struct database_node));
    insert_new_node(node_0, node_1, 2, 200);
    insert_new_node(node_1, node_2, 3, 300);
    node_2->next_node = NULL; //End link list

	printf("Before updating:\n");
	display_linked_list(node_0);

	update_node_at_index(node_0, 1, 23, 1234);

	printf("\nAfter updating:\n");
	display_linked_list(node_0);

    return 0; 
} 
```

# Delete

Delete node at specific index (at index 0, middle index and the last index):

```c
//Other operations like in create_and_read_linked_list.c
void delete_node_at_index(struct database_node *first_node, int index){
    struct database_node *current_node = first_node, *prev_node;
    prev_node = (struct database_node *)malloc(sizeof(struct database_node));
    
    int tmp_index = 0;

    if (tmp_index == index) {      
		*first_node = *(first_node->next_node);
		first_node = first_node->next_node;

        return;
    }

    while(current_node != NULL)
	{        
        if (tmp_index == index) {
            prev_node->next_node = current_node->next_node;
            return;
        }
        prev_node = current_node;  
        current_node = current_node->next_node;
        tmp_index++;
    }
   
    return;
}
//Other operations like in create_and_read_linked_list.c
```
