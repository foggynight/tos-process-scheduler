# TempleOS Research Project

## Setup

Various formats of the final report and research document have been included,
the following commands will copy the `pdf` formatted documents to the root
directory of the project.

```bash
cp ./report/report.pdf .
cp ./research/research.pdf .
```

The `report.pdf` document is the final report for the project, but
`research.pdf` contains much of the same information in a less formal manner.

View `simulation/README.md` for information on how to use the simulation
program.

## Directory Structure

```
report: Final report
|_ report.<pdf...>

research: Research and discussion
|_ research.<pdf...>

simulation: Simulation programming
|_ src: Source code
  |_ list: Various linked list implementations
    |_ circular_double_link.<c/h>: Circular doubly linked list
    |_ single_link.<c/h>: Singly linked list
  |_ test: Unit tests
    |_ test_circular_double_link.<c/h>
    |_ test_single_link.<c/h>
  |_ adam.<c/h>: Adam Task simulation
  |_ config.h: Program configuration
  |_ main.c: Simulation entry point
  |_ process.<c/h>: Process type and helper functions
  |_ ready_queue.<c/h>: Scheduler ready queue
  |_ seth.<c/h>: Seth Task simulation
|_ makefile
|_ project-processes.txt: Simulation input file
|_ README.md: Simulation readme

README.md: Project readme
```
