/** list/single_link.h
 * - Definition of the sl_node_t type representing a node in a singly
 *   linked list
 * - Maintain a head and a tail pointer
 * - Functions to create and destroy an sl_node_t
 * - Functions to add or remove an sl_node_t from a list of
 *   sl_node_t-s */

#ifndef SINGLE_LINK_H
#define SINGLE_LINK_H

/** sl_node_t: Generic singly linked list node. */
typedef struct sl_node_t {
    void *val;              // Pointer to the value of the node
    struct sl_node_t *next; // Pointer to the next node in the list
} sl_node_t;

/* START: NODE FUNCTIONS */

/** sl_create_node: Create a new sl_node_t.
 * @return New sl_node_t with all members initialized to zero */
sl_node_t *sl_create_node(void);

/* END: NODE FUNCTIONS */

/* START: LIST FUNCTIONS */

/** sl_add_node: Add an sl_node_t to a list of sl_node_t-s.
 * @param list_head Pointer to the head of the list
 * @param list_tail Pointer to the tail of the list
 * @param new_node  Node to add to the list */
void sl_add_node(sl_node_t **list_head, sl_node_t **list_tail, sl_node_t *new_node);

/** sl_remove_node: Remove an sl_node_t from a list of sl_node_t-s.
 * @param list_head Pointer to the head of the list
 * @param list_tail Pointer to the tail of the list
 * @param new_node  Node to remove from the list */
void sl_remove_node(sl_node_t **list_head, sl_node_t **list_tail, sl_node_t *target);

/* END: LIST FUNCTIONS */

#endif
