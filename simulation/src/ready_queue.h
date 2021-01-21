/** ready_queue.h
 * Process scheduler ready queue and helper functions.
 *
 * - Requires external semaphore to signal available processes
 * - Used by Adam and Seth Tasks to transfer process data */

#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include "list/single_link.h"
#include "process.h"

/** ready_enqueue: Enqueue a process to the ready queue.
 * @param new_process Process to enqueue */
void ready_enqueue(process_t *new_process);

/** ready_dequeue: Dequeue a process from the ready queue.
 * @return Process to begin executing */
process_t *ready_dequeue(void);

/** ready_queue_empty: Check if the ready queue is empty.
 * @return Zero if the list is empty, else non-zero */
int ready_queue_empty(void);

#endif
