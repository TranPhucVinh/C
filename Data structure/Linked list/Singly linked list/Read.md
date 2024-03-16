# Read the whole linked list

Check [create_and_read_linked_list.c](create_and_read_linked_list.c) source code, with function ``display_linked_list()`` to display the whole linked list. Note that ``first_node`` as parameter of ``display_linked_list()`` must be passed by reference as linked list performs traversing based on the address, which started from first node.

# Read a node at specific index

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

# Size of a linked list

Size of the linked list can only be gotten by traversing the whole list.

## Get the middle member of the linked list by 1 time traversing

To get the middle member of the linked list, beside the traditional way is to [get the list size](#size-of-a-linked-list) first for later calculate the index of the middle member, the middle member can be access by 1 time traversing. The algorithm is to use [two pointer](https://github.com/TranPhucVinh/C/blob/master/Algorithms/Two%20pointers.md), ``p1`` and ``p2``.

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