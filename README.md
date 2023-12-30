# Job Scheduler

This is a simple job scheduler program that reads a workload file and applies different scheduling policies to arrange the jobs. The supported scheduling policies include FIFO, SJF (Shortest Job First), and RR (Round Robin).

## Project Overview

The project consists of the following files:

- `scheduler.c`: The main source code file containing the implementation of job scheduling and analysis functions.
- `scheduler.h`: Header file with the job struct, constants, and function prototypes.
- `Makefile`: Makefile for compiling the project.
- `workload_*.in`: Sample workload files for testing different scenarios.

## Building the Project

To build the project, use the provided Makefile. Open a terminal and run:

```bash
make
```

This will compile the `scheduler.c` file and create an executable named `scheduler`.

## Running the Scheduler

To run the scheduler, execute the compiled binary with the following command:

```bash
./scheduler <scheduling_policy> <workload_file> <time_slice>
```

- `<scheduling_policy>`: Specify the scheduling policy (FIFO, SJF, RR).
- `<workload_file>`: Path to the workload file containing job information.
- `<time_slice>`: Time slice for the RR scheduling policy (not applicable for FIFO and SJF).

## Sample Workloads

The repository includes several sample workload files (`workload_*.in`) to test different scenarios.
