#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include "list/circular_double_link.h"
#include "process.h"
#include "ready_queue.h"
#include "seth.h"

void *seth_start(void *arg)
{
    int id = ((seth_arg_t*)arg)->id;                // ID of this seth thread
    sem_t *sem = ((seth_arg_t*)arg)->sem;           // Semaphore to signal available processes
    pthread_mutex_t *mut = ((seth_arg_t*)arg)->mut; // Killswitch lock

    cdl_node_t *head = NULL; // Head of the thread process list

    /* Wait for and execute processes. Loop condition checks if adam
     * thread killswitch has been locked. If killswitch is unlocked
     * then exit loop, killswitch is re-locked before loop exits. */
    while (head || !ready_queue_empty() || pthread_mutex_trylock(mut)) { // While there are processes remaining or killswitch is locked
        if (!head) { // If thread process list is empty, fetch a new process
            if (sem_wait(sem)) { // Wait for adam thread to signal an available process
                perror("Error");
                exit(1);
            }
            /* If adam thread has signalled but there is no process
             * available to fetch: adam thread has instead signalled to
             * kill and loop will exit. */
            if (!ready_queue_empty()) {
                process_t *process = ready_dequeue(); // Fetch process from ready queue

                cdl_node_t *new_node = cdl_create_node(); // Create new node for process
                new_node->val = process;                  // Point node value member at fetched process

                head = cdl_add_node(head, new_node); // Add node to thread process list
            }
        }
        else { // Thread has a process to execute
            process_t *process = head->val;     // Fetch the process at the head of the thread process list
            head = cdl_remove_node(head, head); // Remove head of the thread process list
            simulate_process(id, process);      // Simulate the execution of the process
        }
    }

    if (pthread_mutex_unlock(mut)) { // Unlock killswitch for other seth threads
        perror("Error");
        exit(1);
    }

    pthread_exit(NULL); // Kill seth thread
}
