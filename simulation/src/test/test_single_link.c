#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../list/single_link.h"

#define LISTLENGTH 5

int main(void)
{
    sl_node_t *head, *tail, *walk;

    /* Create a list of integers */
    head = tail = NULL;
    for (int i = 0; i < LISTLENGTH; ++i) {
        sl_node_t *new_node = sl_create_node();
        assert(new_node);

        new_node->val = malloc(sizeof(int));
        assert(new_node->val);

        *(int*)(new_node->val) = i;
        sl_add_node(&head, &tail, new_node);

        assert(head);
        assert(tail);

        assert(tail->next == NULL);
    }

    /* Test each node value before manipulating list */
    walk = head;
    for (int i = 0; walk && i < LISTLENGTH; ++i) {
        assert(*(int*)walk->val == i);
        walk = walk->next;
    }

    /* Remove every second node starting with the first */
    walk = head;
    for (int i = 0; walk && i < LISTLENGTH; i += 2) {
        sl_node_t *next = walk->next ? walk->next->next : NULL;
        sl_remove_node(&head, &tail, walk);
        walk = next;
    }
    walk = head;
    for (int i = 1; walk && i < LISTLENGTH; i += 2) {
        assert(*(int*)walk->val == i);
        walk = walk->next;
    }

    /* Destroy the list head first */
    walk = head;
    while (walk) {
        sl_remove_node(&head, &tail, walk);
        walk = head;
    }
    assert(!head);
    assert(!tail);

    /* Create a list of integers */
    head = tail = NULL;
    for (int i = 0; i < LISTLENGTH; ++i) {
        sl_node_t *new_node = sl_create_node();
        assert(new_node);

        new_node->val = malloc(sizeof(int));
        assert(new_node->val);

        *(int*)(new_node->val) = i;
        sl_add_node(&head, &tail, new_node);

        assert(head);
        assert(tail);

        assert(tail->next == NULL);
    }

    /* Destroy the list tail first */
    walk = head;
    while (head) {
        assert(tail);
        sl_remove_node(&head, &tail, tail);
        if (head)
            assert(tail);
        if (tail)
            assert(head);
    }
    assert(!head);
    assert(!tail);

    puts("test_single_link: All tests passed.");
    return 0;
}
