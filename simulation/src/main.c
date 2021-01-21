/**
 * COMP2004 - Term Project
 * Robert Coffey - 2020-12-11
 *
 * Kernel process scheduler simulation.
 * Chosen OS: TempleOS by Terry Davis
 *
 * TempleOS uses master-slave and asymmetric processing, employing the
 * First-Come-First-Serve algorithm for process scheduling.
 *
 * See README.md for more information.
 */

#include <pthread.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adam.h"
#include "config.h"
#include "list/single_link.h"
#include "process.h"
#include "seth.h"

#define DFLT_THRD_CNT  8   // Default number of threads
#define MASTER_CORE    0   // Index of the master core in the thread ID array
#define MAX_INPUT_LINE 120 // Maximum input line length

/** get_thread_count: Get the number of threads to simulate.
 *
 * This positive integer value can be passed as a command line argument
 * to the program, otherwise it will be gotten from input within the
 * program.
 *
 * Should the function receive an invalid number of threads, the
 * default number of threads will be used instead.
 *
 * This function prints its results to the stdin stream.
 *
 * @param argc The number of command line arguments
 * @param argv Pointer to the command line arguments
 *
 * @return Number of threads to simulate */
static int get_thread_count(int argc, char **argv);

/** parse_input: Parse a line of input.
 *
 * This function converts the comma separated fields of an input string
 * into integers, and stores them in the result array of integers.
 *
 * @param result Array of integers to store result
 * @param input  Line of input to parse */
static void parse_input(int *result, char *input);

#ifndef DISABLE_EXTRA_FUNCTIONS
/** print_process_list: Print a table of the list of processes.
 * @param head Head of the list of processes to print */
static void print_process_list(sl_node_t *head);
#endif

int main(int argc, char **argv)
{
    srand(clock()); // Seed the pseudo random number generator

    FILE *input_file = fopen("project-processes.txt", "r"); // Open the input file
    if (!input_file) {
        perror("Error");
        return 1;
    }

    char input[MAX_INPUT_LINE+2];    // Input line storage, extra two bytes for '\n' and '\0'
    int result[PROCESS_FIELD_COUNT]; // Input value storage, used when creating a process

    sl_node_t *head = NULL, *tail = NULL; // Head and tail of the list of processes

    while (fgets(input, MAX_INPUT_LINE+1, input_file)) { // Store line of text from the input file in input
        if (input[0] == '#' || input[0] == '\n') // Ignore comments and empty lines
            continue;
        input[strcspn(input, "\n")] = '\0'; // Remove newline character from input string

        parse_input(result, input);                      // Store the input fields, converted to integers, in the result array
        process_t *new_process = create_process(result); // Create a new process using the result array

        sl_node_t *new_node = sl_create_node(); // Create a new list node
        new_node->val = (void*)new_process;     // Point the val pointer of the new list node to the new process

        sl_add_node(&head, &tail, new_node); // Add the new list node to the list of processes
    }

    fclose(input_file); // Close the input file

    /* Create arg for adam thread start_routine */
    adam_arg_t *adam_arg = malloc(sizeof(adam_arg_t));
    adam_arg->head = head;
    adam_arg->tail = tail;
    adam_arg->count = get_thread_count(argc, argv); // Get initial number of available threads

    /* Create adam thread representing the master core */
    pthread_t adam_tid;
    if (pthread_create(&adam_tid, 0, adam_start, adam_arg)) {
        perror("Error");
        return 1;
    }

    /* Join adam thread */
    void *res;
    if (pthread_join(adam_tid, &res)) {
        perror("Error");
        return 1;
    }

    return 0;
}

static int get_thread_count(int argc, char **argv)
{
    int thread_count = 0;

    if (argc > 2) { // Too many command line arguments
        fprintf(stderr,
            "Error: Too many arguments\n"
            "Usage: %s [THREAD_COUNT]\n",
            argv[0]);
        return 1;
    }
    else if (argc < 2) { // No thread count argument was provided
        printf("Number of threads to simulate: ");
        scanf(" %d", &thread_count);
    }
    else { // thread_count argument was provided
        thread_count = atoi(argv[1]);
    }

    if (thread_count < 2) { // Invalid thread count
        printf("Invalid usage: Number of threads must be greater than one\n"
               "Using default number of threads: %d\n",
            DFLT_THRD_CNT);
        thread_count = DFLT_THRD_CNT;
    }

    printf("Adam threads: 1\n"
           "Seth threads: %d\n",
        thread_count - 1);

    return thread_count;
}

static void parse_input(int *result, char *input)
{
    regex_t regex;        // Reusable regex container
    regmatch_t pmatch[1]; // Regex expression match storage

    /* Check for valid input string using a regex expression */
    if (regcomp(&regex, "^P[0-9]*,[0-9]*,[0-9]*,[0-9]*,[0-9]*,[0-9]*$", 0)) { // Prepare regex expression matching the entire input string
        fputs("Error: Regex failure\n", stderr);
        exit(1);
    }
    else if (regexec(&regex, input, 0, NULL, 0)) { // Execute regex expression on the input string
        fputs("Error: Invalid input\n", stderr);
        exit(1);
    }

    *input = ','; // Convert 'P' to ',' to make each field of the input string an integer prepended with a comma

    /* Extract the process fields from the input string */
    if (regcomp(&regex, ",[0-9]*", 0)) { // Prepare regex expression matching a single field of the input string
        fputs("Error: Regex failure\n", stderr);
        exit(1);
    }
    for (int i = 0; i < PROCESS_FIELD_COUNT; ++i) { // For each field of the input string
        if (regexec(&regex, input, 1, pmatch, 0)) { // Execute regex expression on the input string
            fputs("Error: Invalid input\n", stderr);
            exit(1);
        }

        char str[MAX_INPUT_LINE / PROCESS_FIELD_COUNT]; // Storage for input match
        int len = pmatch[0].rm_eo - pmatch[0].rm_so;    // Get the length of the match

        sprintf(str, "%.*s\n",
            len, input + pmatch[0].rm_so + 1); // Extract the match from the input string while slicing off the comma
        result[i] = atoi(str);                 // Convert the modified match to an integer

        input += len; // Slice off the match from the input string
    }
}

#ifndef DISABLE_EXTRA_FUNCTIONS
static void print_process_list(sl_node_t *head)
{
    if (!head) {
        printf("List empty\n");
    }
    else {
        int count = 0;
        sl_node_t *walk = head;
        printf("\n          %4s %4s %4s %4s %4s %4s\n",
            "PN", "AT", "P", "BT", "TB", "MS");
        while (walk) {
            process_t p = *(process_t*)(walk->val);
            printf("Node %3d: %4d %4d %4d %4d %4d %4d\n",
                ++count, p.process_number, p.arrival_time, p.priority,
                p.cpu_burst_time, p.total_bursts, p.memory_size);
            walk = walk->next;
        }
    }
}
#endif
