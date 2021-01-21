#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "process.h"
#include "time.h"

/** print_process: Print process data.
 * @param process Process to print */
static void print_process(process_t *process);

process_t *create_process(int members[]) {
    process_t *new_process = malloc(sizeof(process_t));
    if (!new_process) {
        perror("Error");
        exit(1);
    }

    new_process->process_number = members[0];
    new_process->arrival_time = members[1];
    new_process->priority = members[2];
    new_process->cpu_burst_time = members[3];
    new_process->total_bursts = members[4];
    new_process->memory_size = members[5];

    return new_process;
}

void destroy_process(process_t *target)
{
    free(target);
}

void simulate_process(int thread_id, process_t *process)
{
    int total_time = rand()%MAX_TOTAL_TIME; // Pre-calculated total running time of the process in milliseconds

    puts("Simulating process");
    printf("|_ THREAD: %d\n", thread_id);
    printf("|_ "); print_process(process); putchar('\n');

    #ifdef ENABLE_THREAD_LOGGING
    printf("THREAD %d: ", thread_id);
    print_process(process); // Print the initial process data
    puts(", DURATION: 0");
    #endif

    int duration = 0; // Current running time of the process in milliseconds
    for (int time = total_time; time > 0; time -= process->cpu_burst_time) {
        int sleep_time = process->cpu_burst_time; // Sleep time in milliseconds of the simulated process
        if (time - sleep_time < 0) // If remaining time was less than burst time
            sleep_time -= time; // Offset sleep_time by the difference of remaining time and burst time

        process->memory_size += rand()%MAX_MEMORY_INC; // Increase memory size of the process by a random amount
        ++process->total_bursts;                       // Increment the burst count of the process

        duration = total_time-time+sleep_time;

        #ifdef ENABLE_THREAD_LOGGING
        printf("THREAD %d: ", thread_id);
        print_process(process); // Print the updated process data
        printf(", DURATION: %d\n", duration);
        #endif

        poll(0, 0, sleep_time); // Blocking sleep for sleep_time milliseconds
    }

    puts("Process complete");
    printf("|_ THREAD: %d\n", thread_id);
    printf("|_ "); print_process(process); putchar('\n');
    printf("|_ DURATION: %d\n", duration);
}

static void print_process(process_t *process)
{
    printf("PN: P%d, AT: %2d, P: %2d, BT: %2d, TB: %3d, MS: %3d",
        process->process_number, // PN: Process number
        process->arrival_time,   // AT: Arrival time
        process->priority,       // P:  Priority
        process->cpu_burst_time, // BT: CPU burst time
        process->total_bursts,   // TB: Total bursts
        process->memory_size);   // MS: Memory size
}
