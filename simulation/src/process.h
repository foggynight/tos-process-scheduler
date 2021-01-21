/** process.h
 * Definition and functions to create a process_t, representing a
 * process to simulate. */

#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_FIELD_COUNT 6 // Number of fields in process struct

/** process_t: Storage for the data of a simulated process.
 * - Store data for the start_routine of a pthread
 * - Pass pointer to process as the final argument of pthread_create */
typedef struct process_t {
    int process_number; // Process identifier: PID
    int arrival_time;   // Arrival time (ms)
    int priority;       // Scheduler priority
    int cpu_burst_time; // CPU burst time (ms)
    int total_bursts;   // Total bursts
    int memory_size;    // Memory size (kb)
} process_t;

/** create_process: Create a new process, destroy using destroy_process.
 * @param members Array of initial process member values
 * @return Pointer to new process */
process_t *create_process(int members[]);

/** destroy_process: Destroy the target process.
 * @param target Pointer to target process */
void destroy_process(process_t *target);

/** simulate_process: Simulate the execution of a process.
 * @param thread_id ID of the caller thread
 * @param process   Initial data of the process to simulate */
void simulate_process(int thread_id, process_t *process);

#endif
