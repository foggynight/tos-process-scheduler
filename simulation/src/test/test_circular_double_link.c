#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../list/circular_double_link.h"

#define LISTLENGTH 5

int main(void)
{
    cdl_node_t *head, *tail, *walk;

    /* Create the list of integers */
    head = tail = NULL;
    for (int i = 0; i < LISTLENGTH; ++i) {
        cdl_node_t *new_node = cdl_create_node();
        assert(new_node);

        assert((new_node->val = malloc(sizeof(int))));
        *(int*)(new_node->val) = i;

        head = cdl_add_node(head, new_node);
        assert(head);
    }

    /* Test each node value before manipulating list */
    walk = head;
    for (int i = 0; walk && i < LISTLENGTH; ++i) {
        assert(*(int*)walk->val == i);
        walk = walk->next;
    }

    /* Remove every second node starting with the first */
    walk = head;
    for (int i = 0; head && i < LISTLENGTH; i += 2) {
        cdl_node_t *next = (walk != walk->next) ? walk->next->next : NULL;
        head = cdl_remove_node(head, walk);
        walk = next;
    }
    walk = head;
    for (int i = 1; i < LISTLENGTH; i += 2) {
        assert(*(int*)walk->val == i);
        walk = walk->next;
    }

    /* Empty the list */
    walk = head;
    while (head) {
        cdl_node_t *next = walk->next;
        head = cdl_remove_node(head, walk);
        walk = next;
    }
    assert(!head);
    assert(!tail);

    puts("test_circular_double_link: All tests passed.");
    return 0;
}
