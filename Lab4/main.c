#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define MSGSIZE 20    // maximum pipe message size
#define MEMSIZE 1024  // shared memory size

char *msg = "No, yo soy tu padre."; // for the cultured
char buffer[MSGSIZE];
key_t key = 255;
char *data; // pointer to shared memory

// Pipeline initialization
void pipe_init(int *p) {
    if (pipe(p) < 0) {
        printf("Pipe fail \n");
        exit(1);
    }
}
// Shared memory initialization
void shared_memory_init() {
    int shmid = shmget(key, MEMSIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    data = (char  *) shmat(shmid, NULL, 0);
}
// Parent process
void parent_process(int cnum, int *pipe) {
    printf("[P] Parent process ID=%d\n", getpid());
    // Send message via pipe
    close(pipe[0]);
    write(pipe[1], msg, MSGSIZE);
    printf("[P] Sending message through pipe: %s\n", msg);
    close(pipe[1]);
    // Write in shared memory
    strcpy(data, "Nooooooo!");
    printf("[P] Data written to shared memory.\n");
    // Wait for children to finish
    for (int j=0; j<cnum; j++) {
        wait(NULL);
    }
    printf("[P] All child processes finished.\n");
}
// Children process
void child_process(int i, int *pipe) {
    printf("[C%d] Child process ID=%d\n", i, getpid());
    // Identify parent process
    printf("[C%d] Child's parent ID=%d\n", i, getppid());
    // Read received message from pipe
    close(pipe[1]);
    read(pipe[0], buffer, MSGSIZE);
    printf("[C%d] Reading received message from pipe: %s\n", i, buffer);
    close(pipe[0]);
    // Read data from shared memory
    printf("[C%d] Data found in shared memory: %s\n", i, data);
    // Stop execution once the child is done
    exit(0);
}

int main() {
    // Create pipe
    int pipe[2]; // p[0] -> read, p[1] -> write
    pipe_init(pipe);
    // Create shared memory
    shared_memory_init();

    // Fork parent process into three child processes
    pid_t cpid;
    int status;
    int cnum = 3;
    for (int i=0; i<cnum; i++) {
        cpid = fork();
        if (cpid < 0) {
            perror("fork fail");
            exit(1);
        } else if (cpid == 0) {
            child_process(i, pipe);
        }
    }
    parent_process(cnum, pipe);
    shmdt(data);
    return 0;
}