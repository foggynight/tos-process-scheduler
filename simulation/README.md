# TempleOS Simulation Programming

## Description

This program reads a list of inputs from `project-processes.txt` in
CSV format, each line representing a process to simulate.

To simulate a process, the scheduler assigns the process to a thread,
and that thread alternates between updating the process data, and
sleeping for the alloted burst time to represent a CPU burst.

## Configuration

There are various macros defined in the `src/config.h` file, these
macros may be commented-out or modified to change the program
configuration.

##### General
- `DISABLE_EXTRA_FUNCTIONS`: Disable debugging functions
- `ENABLE_THREAD_LOGGING`: Log thread progress

##### Process Simulation
- `MAX_TOTAL_TIME`: Max total time in milliseconds for a process to execute
- `MAX_MEMORY_INC`: Max memory increment per CPU burst

## Installation

- `make`: Build normally
- `make debug`: Build with debug flag
- `make test`: Build, execute, and cleanup test suite

## Usage

```bash
./kernel [THREAD_COUNT]
./kernel [THREAD_COUNT] >results.txt
```

- Should `THREAD_COUNT` be omitted, it will be obtained from a prompt
  within the program.
- If `THREAD_COUNT` is invalid, the default thread count from
  `src/config.h` will be used instead.
