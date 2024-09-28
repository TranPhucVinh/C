# [Update node value at a specific index](update_at_specific_index.c)
# Reverse the linked list
* Use stack: Put all member into a stack, then start popping them out (as LIFO) so that the last member of the linked list is now the first one
* Use recurive
```c
typedef struct LinkList LinkList;
LinkList* _head;
struct LinkList* reverseList(struct LinkList* head) {
    _head = head;
    reverse(NULL, _head);
    return _head;
}

void reverse(LinkList *prev, LinkList *current) {
    if (current == NULL) {
        _head = prev;
        return;
    }
    LinkList *next = current->next;
    current->next = prev;
    reverse(current, next);
}
```
