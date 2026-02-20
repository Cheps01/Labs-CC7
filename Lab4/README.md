# Lab 4

This project demonstrates the fundamentals of process creation and communication in a Unix-like environment using C. It showcases two primary IPC mechanisms: **Pipes** and **Shared Memory**.

## Overview

The program initializes IPC resources, spawns three child processes, and sets up communication between the parent and its children.

### 1. Process Creation
Processes are created using the `fork()` system call within a loop in `main.c`. 
- **`fork()`**: When called, it creates a new process (child) by duplicating the calling process (parent).
- **Execution Flow**: The child processes execute the `child_process()` function and then exit. The parent process continues to the `parent_process()` function, where it coordinates the communication and waits for all children to terminate using `wait(NULL)`.

### 2. IPC Mechanisms

#### Pipes
Pipes provide a unidirectional communication channel.
- **Initialization**: A pipe is created using `pipe(int pipefd[2])`, where `pipefd[0]` is the read end and `pipefd[1]` is the write end.
- **Communication**: The parent writes a message ("No, yo soy tu padre.") to the pipe. The children read this message. Note that since multiple children are reading from the same pipe, the first one to reach the `read()` call will consume the data.

#### Shared Memory
Shared memory allows multiple processes to access the same segment of RAM.
- **Initialization**: 
    - `shmget()` creates a shared memory segment associated with a specific key.
    - `shmat()` attaches the segment to the process's address space.
- **Communication**: The parent writes "Nooooooo!" into the shared memory segment. Unlike pipes, data in shared memory persists and can be read by all child processes simultaneously without being consumed.

## How to Run

### Compilation
Use `gcc` to compile the source code:
```bash
gcc main.c -o lab4
```

### Execution
Run the compiled binary:
```bash
./lab4
```

## Expected Output
The output will display the PIDs of the parent and children, the message transferred through the pipe, and the data retrieved from shared memory.