#include <stdio.h>
#include <stdlib.h>

#include "circular_double_link.h"

cdl_node_t *cdl_create_node(void)
{
    cdl_node_t *new_node = calloc(1, sizeof(cdl_node_t));
    if (!new_node) {
        perror("Error");
        exit(1);
    }
    return new_node;
}

/** cdl_destroy_node: Destroy a cdl_node_t.
 * @param target Target cdl_node_t to destroy */
static void cdl_destroy_node(cdl_node_t *target)
{
    if (!target) {
        fputs("Error: Cannot destroy NULL", stderr);
        exit(1);
    }
    free(target);
}

cdl_node_t *cdl_add_node(cdl_node_t *list_head, cdl_node_t *new_node)
{
    if (!new_node) { // Node to add is NULL
        fputs("Error: Cannot add NULL to list\n", stderr);
        exit(1);
    }

    if (!list_head) { // List is empty
        list_head = new_node->prev = new_node->next = new_node;
    }
    else if (list_head->next == list_head) { // List contains only list_head
        list_head->prev = list_head->next = new_node;
        new_node->prev = new_node->next = list_head;
    }
    else { // There are multiple nodes in the list
        list_head->prev->next = new_node;
        new_node->prev = list_head->prev;

        list_head->prev = new_node;
        new_node->next = list_head;
    }

    return list_head;
}

cdl_node_t *cdl_remove_node(cdl_node_t *list_head, cdl_node_t *target)
{
    if (!list_head) { // List is empty
        fputs("Error: Cannot remove node from empty list\n", stderr);
        exit(1);
    }
    if (!target) { // Node to remove is NULL
        fputs("Error: Cannot remove NULL from list\n", stderr);
        exit(1);
    }

    if (target->next == target) { // Node to remove is the only node in the list
        list_head = NULL;
    }
    else if (target == list_head) { // Node to remove is list_head
        list_head = list_head->next;
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    else { // Node to remove is not list_head
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    cdl_destroy_node(target);
    return list_head;
}
