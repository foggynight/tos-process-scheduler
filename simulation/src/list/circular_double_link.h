/** list/circular_double_link.h
 * - Definition of the cdl_node_t type representing a node in a circular
 *   doubly linked list
 * - Maintain a head pointer
 * - Functions to create and destroy a cdl_node_t
 * - Functions to add or remove a cdl_node_t from a list of
 *   cdl_node_t-s */

#ifndef CIRCULAR_DOUBLE_LINK_H
#define CIRCULAR_DOUBLE_LINK_H

/** cdl_node_t: Generic circular doubly linked list node. */
typedef struct cdl_node_t {
    void *val;               // Pointer to the value of the node
    struct cdl_node_t *prev; // Pointer to the previous node in the list
    struct cdl_node_t *next; // Pointer to the next node in the list
} cdl_node_t;

/* --- START: NODE FUNCTIONS --- */

/** cdl_create_node: Create a new cdl_node_t.
 * @return New cdl_node_t with all members initialized to zero */
cdl_node_t *cdl_create_node(void);

/* --- END: NODE FUNCTIONS --- */

/* --- START: LIST FUNCTIONS --- */

/** cdl_add_node: Add a cdl_node_t to a list of cdl_node_t-s.
 * @param list_head Head of the list
 * @param new_node  Node to add to the list
 * @return Head of the list */
cdl_node_t *cdl_add_node(cdl_node_t *list_head, cdl_node_t *new_node);

/** cdl_remove_node: Remove a cdl_node_t from a list of cdl_node_t-s.
 * @param list_head Head of the list
 * @param new_node  Node to remove from the list
 * @return Head of the list */
cdl_node_t *cdl_remove_node(cdl_node_t *list_head, cdl_node_t *target);

/* --- END: LIST FUNCTIONS --- */

#endif
