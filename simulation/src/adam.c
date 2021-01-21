#include <poll.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include "adam.h"
#include "list/single_link.h"
#include "process.h"
#include "ready_queue.h"
#include "seth.h"

#define TIME_INC 1 // Time increment value for readability

void *adam_start(void *arg)
{
    adam_arg_t *adam_arg = (adam_arg_t*)arg; // Process list head and tail, as well as thread count
    int thread_count = adam_arg->count;      // Store thread count for readability

    /* Create semaphore to signal available processes */
    sem_t *sem = malloc(sizeof(sem_t));
    if (!sem || sem_init(sem, 0, 0)) {
        perror("Error");
        exit(1);
    }

    /* Create mutex representing kill switch */
    pthread_mutex_t *mut = malloc(sizeof(pthread_mutex_t));
    if (!mut || pthread_mutex_init(mut, NULL) || pthread_mutex_lock(mut)) {
        perror("Error");
        exit(1);
    }

    /* Create seth threads representing slave cores */
    pthread_t *seth_tids = malloc((thread_count - 1) * sizeof(pthread_t));
    seth_arg_t *seth_args = malloc((thread_count - 1) * sizeof(seth_arg_t));
    if (!seth_tids || !seth_args) {
        perror("Error");
        exit(1);
    }
    for (int i = 0; i < thread_count-1; ++i) {
        seth_args[i].id = i;
        seth_args[i].sem = sem;
        seth_args[i].mut = mut;

        if (pthread_create(&seth_tids[i], 0, seth_start, &seth_args[i])) {
            perror("Error");
            exit(1);
        }
    }

    /* Send processes to the scheduler */
    for (int time = 0; adam_arg->head; time += TIME_INC) { // While the process list is not empty
        for (sl_node_t *next, *node = adam_arg->head; node; node = next) { // For each node in the process list
            next = node->next;
            if (((process_t*)(node->val))->arrival_time == time) { // If current time is the process arrival time
                ready_enqueue((process_t*)(node->val));                 // Enqueue the process in the ready queue
                sl_remove_node(&adam_arg->head, &adam_arg->tail, node); // Remove the process from the list of processes

                if (sem_post(sem)) { // Signal available process
                    perror("Error");
                    exit(1);
                }
            }
        }
        poll(0, 0, TIME_INC); // Blocking sleep for TIME_INC milliseconds
    }

    /* Release seth threads from slavery */
    if (pthread_mutex_unlock(mut)) { // Unlock killswitch
        perror("Error");
        exit(1);
    }
    for (int i = 0; i < thread_count-1; ++i) { // Signal to free seth threads from waiting
        if (sem_post(sem)) {
            perror("Error");
            exit(1);
        }
    }

    /* Join seth threads */
    void *res;
    for (int i = 0; i < adam_arg->count-1; ++i) {
        if (pthread_join(seth_tids[i], &res)) {
            perror("Error");
            exit(1);
        }
    }

    free(seth_args);
    free(seth_tids);
    free(sem);

    pthread_exit(NULL);
}
