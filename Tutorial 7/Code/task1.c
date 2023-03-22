#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 1024

typedef struct proc{
    char name[MAX_NAME_LEN];
    int priority;
    int pid;
    int runtime;
}proc_t;

typedef struct queue {
    proc_t process;
    struct queue* next;
}queue_t;


void push(queue_t** queue, proc_t process) {
    queue_t* new_node = (queue_t*) malloc(sizeof(queue_t));
    new_node->process = process;
    new_node->next = *queue;
    *queue = new_node;
}

int main(void){
    //Variables
    char line[MAX_LINE_LEN];
    char* name_str;
    char* priority_str;
    char* pid_str;
    char* runtime_str;
    proc_t process;
    queue_t* queue = NULL;
    
    // Open the file containing the processes
    FILE *fp = fopen("processes.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read the file line by line
    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        // extract fields from line
        name_str = strtok(line, ",");
        priority_str = strtok(NULL, ",");
        pid_str = strtok(NULL, ",");
        runtime_str = strtok(NULL, ",");

        // parse values and create process struct
        strncpy(process.name, name_str, MAX_NAME_LEN);
        process.priority = atoi(priority_str);
        process.pid = atoi(pid_str);
        process.runtime = atoi(runtime_str);

        // add process to queue
        push(&queue, process);
    }

    // Close the file
    fclose(fp);

    queue_t* curr_node = queue;
    while (curr_node != NULL) {
        printf("Name: %s\nPriority: %d\nPID: %d\nRuntime: %d", 
            curr_node->process.name, curr_node->process.priority,
            curr_node->process.pid, curr_node->process.runtime);
        curr_node = curr_node->next;

        printf("\n\n************************\n");
    }

    return 0;
}