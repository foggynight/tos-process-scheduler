/** seth.h
 *
 * Definition of the seth_t type, representing a TempleOS Seth Task.
 *
 * - All cores have a Seth Task
 * - All Seth Tasks are immortal
 * - All Seth Tasks are slaves to the special Seth Task named Adam
 * - Seth Tasks are the father of all tasks on a given core
 * - Seth Tasks may have multiple processes in queue, this will not be
 *   of use within the simulation */

#ifndef SETH_H
#define SETH_H

#include <pthread.h>
#include <semaphore.h>

/** seth_arg_t: Seth Task start_routine argument. */
typedef struct seth_arg_t {
    int id;                    // ID of the seth thread
    sem_t *sem;                // Pointer to semaphore signalling available processes
    pthread_mutex_t *mut;      // Pointer to mutex lock representing kill switch
} seth_arg_t;

/** seth_start: Start a Seth Task.
 *
 * To be passed as the start_routine of all pthreads other than the
 * pthread representing the master core.
 *
 * @param arg Pointer to a seth_arg_t
 *
 * @return Ignored */
void *seth_start(void *arg);

#endif
