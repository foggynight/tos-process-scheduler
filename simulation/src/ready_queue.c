#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "ready_queue.h"

static sl_node_t *rq_head; // Head of the ready queue
static sl_node_t *rq_tail; // Tail of the ready queue

void ready_enqueue(process_t *new_process)
{
    if (!new_process) {
        fputs("Error: Cannot enqueue NULL", stderr);
        exit(1);
    }

    sl_node_t *new_node = sl_create_node();
    new_node->val = new_process;

    sl_add_node(&rq_head, &rq_tail, new_node);
}

process_t *ready_dequeue(void)
{
    if (!rq_head) {
        fputs("Error: Cannot dequeue from NULL", stderr);
        exit(1);
    }

    process_t *process = (process_t*)rq_tail->val;
    sl_remove_node(&rq_head, &rq_tail, rq_tail);

    return process;
}

int ready_queue_empty(void)
{
    return rq_head ? 0 : 1;
}
