#include <stdio.h>
#include <stdlib.h>

#include "single_link.h"

sl_node_t *sl_create_node(void)
{
    sl_node_t *new_node = calloc(1, sizeof(sl_node_t));
    if (!new_node) {
        perror("Error");
        exit(1);
    }
    return new_node;
}

/** sl_destroy_node: Destroy an sl_node_t.
 * @param target Target sl_node_t to destroy */
static void sl_destroy_node(sl_node_t *target)
{
    if (!target) {
        fputs("Error: Cannot destroy NULL", stderr);
        exit(1);
    }
    free(target);
}

void sl_add_node(sl_node_t **list_head, sl_node_t **list_tail, sl_node_t *new_node)
{
    if (!new_node) { // Node to add is NULL
        fputs("Error: Cannot add NULL to list\n", stderr);
        exit(1);
    }

    if (!*list_head) { // List is empty
        *list_head = *list_tail = new_node;
    }
    else { // List is not empty
        (*list_tail)->next = new_node;
        *list_tail = new_node;
    }
}

void sl_remove_node(sl_node_t **list_head, sl_node_t **list_tail, sl_node_t *target)
{
    if (!*list_head) { // List is empty
        fputs("Error: Cannot remove node from empty list\n", stderr);
        exit(1);
    }
    if (!target) { // Node to remove is NULL
        fputs("Error: Cannot remove NULL from list\n", stderr);
        exit(1);
    }

    if (*list_head == *list_tail) { // The list contains one element
        sl_destroy_node(*list_head);
        *list_head = *list_tail = NULL;
    }
    else if (target == *list_head) { // Node to remove is list_head
        sl_node_t *old_head = *list_head;
        *list_head = (*list_head)->next;
        sl_destroy_node(old_head);
    }
    else if (target == *list_tail) { // Node to remove is list_tail
        sl_node_t *walk;
        for (walk = *list_head; walk->next != *list_tail; walk = walk->next); // Find the previous node to the list_tail

        sl_destroy_node(walk->next);
        walk->next = NULL;
        *list_tail = walk;
    }
    else { // Node to remove is in the body of the list
        sl_node_t *walk;
        for (walk = *list_head; walk->next != target; walk = walk->next); // Find the previous node to the target

        sl_node_t *targ = walk->next;    // Node to remove
        walk->next = walk->next->next; // Remove the node
        sl_destroy_node(targ);         // Destroy the node
    }
}
