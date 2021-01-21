/** adam.h
 *
 * Definition and functions to create an adam_t, representing the
 * TempleOS Adam Task.
 *
 * - All cores have a Seth Task, the master core's is named Adam
 * - Adam serves as master to the other Seth Tasks
 * - Adam and all other Seth Tasks are immortal
 * - Adam is the father of all other Seth Tasks */

#ifndef ADAM_H
#define ADAM_H

#include "list/single_link.h"

/** adam_arg_t: Adam thread start_routine argument. */
typedef struct adam_arg_t {
    int count;       // Initial number of available threads
    sl_node_t *head; // Process list head
    sl_node_t *tail; // Process list tail
} adam_arg_t;

/** adam_start: Start the Adam Task.
 *
 * To be passed as the start_routine of the pthread representing the
 * master core.
 *
 * @param arg Pointer to an adam_arg_t
 *
 * @return Ignored */
void *adam_start(void *arg);

#endif
