/** config.h: Program configuration. */

/* General config */
#define DISABLE_EXTRA_FUNCTIONS // Comment out to enable extra functions, generates unused warnings
#define ENABLE_THREAD_LOGGING   // Comment out to silence thread progress logging

/* Process simulation config */
#define MAX_TOTAL_TIME 200 // Maximum total time in milliseconds of a simulated process
#define MAX_MEMORY_INC 10  // Maximum memory increment in kilobytes per cpu burst of a simulated process
