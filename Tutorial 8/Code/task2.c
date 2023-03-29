#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Define the maximum amount of memory available
#define MEMORY 1024

// Define the struct for each process
struct proc {
    char name[256];
    int priority;
    int pid;
    int address;
    int memory;
    int runtime;
    bool suspended;
};

// Initialize the global variables
Queue priority;
Queue secondary;
int avail_mem[MEMORY] = {0};

// Function to execute a process
void execute_process(struct proc *p) {
    // Allocate memory for the process
    int i;
    for (i = 0; i < MEMORY; i++) {
        int j;
        for (j = 0; j < p->memory; j++) {
            if (avail_mem[i + j] != 0) {
                break;
            }
        }
        if (j == p->memory) {
            p->address = i;
            for (j = 0; j < p->memory; j++) {
                avail_mem[i + j] = 1;
            }
            break;
        }
    }

    // If there is not enough memory available, push the process back onto the queue
    if (i == MEMORY) {
        printf("Not enough memory available for process %s\n", p->name);
        push(&secondary, p);
        return;
    }

    // Fork and execute the process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        char mem_address[16];
        sprintf(mem_address, "%d", p->address);
        char mem_size[16];
        sprintf(mem_size, "%d", p->memory);
        execlp("./process", "./process", mem_address, mem_size, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        p->pid = pid;
        printf("Executing process %s with priority %d, pid %d, memory %d, runtime %d\n",
            p->name, p->priority, p->pid, p->memory, p->runtime);
        sleep(p->runtime);
        kill(p->pid, SIGTSTP);
        int status;
        waitpid(p->pid, &status, 0);
        p->pid = 0;
        p->suspended = false;
        int j;
        for (j = 0; j < p->memory; j++) {
            avail_mem[p->address + j] = 0;
        }
    }
}

int main() {
    // Initialize the queues
    init_queue(&priority);
    init_queue(&secondary);

    // Open the file
    FILE *file = fopen("processes_q2.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Read the file line by line
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Parse the line into name, priority, memory, and runtime
        char *name = strtok(line, ",");
        int priority = atoi(strtok(NULL, ","));
        int memory = atoi(strtok(NULL, ","));
        int runtime = atoi(strtok(NULL, ","));

        // Allocate memory for the process and initialize its values
        struct proc *p = malloc(sizeof(struct proc));
         strncpy(p->name, name, sizeof(p->name));
         p->priority = priority;    
         p->memory = memory;
         p->runtime = runtime;
         p->pid = 0;
         p->address = 0;
         p->suspended = false;
    // Push the process onto the appropriate queue based on priority
    if (priority == 0) {
        push(&secondary, p);
    } else {
        push(&priority, p);
    }
}

// Close the file
fclose(file);

// Execute the processes in order of priority
while (!is_empty(&priority) || !is_empty(&secondary)) {
    if (!is_empty(&priority)) {
        struct proc *p = front(&priority);
        execute_process(p);
        pop(&priority);
        free(p);
    } else {
        struct proc *p = front(&secondary);
        execute_process(p);
        pop(&secondary);
        free(p);
    }
}

return 0;
}